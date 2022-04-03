#version 330

#define NUM_SPHERES 64
#define PI 3.14159265359
#define DIFF 0
#define SPEC 1
#define REFR 2

struct Ray {
	vec3 origin;
	vec3 direction;
};

struct Sphere {
	float radius;
	vec3 position;
	vec3 e;
	vec3 color;
	int reflection;
	bool visible;
};

uniform sampler2D channel0;
uniform int frame;
uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;
uniform Sphere spheres[NUM_SPHERES];
uniform Sphere lightSourceVolume;
uniform int MAXDEPTH;

in vec2 st;

out vec4 fragColor;

float seed = 0.;
float rand() { return fract(sin(seed++)*43758.5453123); }

float intersect(Sphere s, Ray r) {
	vec3 op = s.position - r.origin;
	float t;
	float epsilon = 1e-3;
	float b = dot(op, r.direction);
	float det = b * b - dot(op, op) + s.radius * s.radius;

	if (det < 0.) {
		return 0.;
	} else  {
		det = sqrt(det);
	}

	return (t = b - det) > epsilon ? t : ((t = b + det) > epsilon ? t : 0.);
}

int intersect(Ray r, out float t, out Sphere s, int avoid) {
	int id = -1;
	t = 1e5;
	s = spheres[0];
	for (int i = 0; i < NUM_SPHERES; ++i) {
		Sphere S = spheres[i];
		if (S.visible) {
			float d = intersect(S, r);
			if (i != avoid && d != 0. && d < t) {
				t = d;
				id = i;
				s = S;
			}
		}
	}
	return id;
}

vec3 jitter(vec3 d, float phi, float sina, float cosa) {
	vec3 w = normalize(d);
	vec3 u = normalize(cross(w.yzx, w));
	vec3 v = cross(w, u);
	return (u*cos(phi) + v*sin(phi)) * sina + w * cosa;
}

vec3 radiance(Ray r) {
	vec3 acc = vec3(0.);
	vec3 mask = vec3(1.);
	int id = -1;

	for (int depth = 0; depth < MAXDEPTH; ++depth) {
		float t;
		Sphere obj;

		if ((id = intersect(r, t, obj, id)) < 0) break;

		vec3 x = t * r.direction + r.origin;
		vec3 n = normalize(x - obj.position);
		vec3 nl = n * sign(-dot(n, r.direction));

		if (obj.reflection == DIFF) {
			float r2 = rand();
			vec3 d = jitter(nl, 2. * PI * rand(), sqrt(r2), sqrt(1. - r2));
			vec3 e = vec3(0.);

			Sphere s = lightSourceVolume;
			int i = 8;

			vec3 l0 = s.position - x;
			float cos_a_max = sqrt(1. - clamp(s.radius * s.radius / dot(l0, l0), 0., 1.));
			float cosa = mix(cos_a_max, 1., rand());
			vec3 l = jitter(l0, 2. * PI * rand(), sqrt(1. - cosa * cosa), cosa);

			if (intersect(Ray(x, l), t, s, id) == i) {
				float omega = 2. * PI * (1. - cos_a_max);
				e += (s.e * clamp(dot(l, n),0.,1.) * omega) / PI;
			}

			float E = 1.;
			acc += mask * obj.e * E + mask * obj.color * e;
			mask *= obj.color;
			r = Ray(x, d);
		} else if (obj.reflection == SPEC) {
			acc += mask * obj.e;
			mask *= obj.color;
			r = Ray(x, reflect(r.direction, n));
		} else {
			float a = dot(n, r.direction);
			float ddn = abs(a);
			float nc = 1.;
			float nt = 1.5;
			float nnt = mix(nc/nt, nt/nc, float(a>0.));
			float cos2t = 1. - nnt * nnt * (1. - ddn * ddn);
			r = Ray(x, reflect(r.direction, n));

			if (cos2t > 0.) {
				vec3 tdir = normalize(r.direction * nnt + sign(a) * n * (ddn * nnt + sqrt(cos2t)));
				float R0 = (nt - nc) * (nt - nc) / ((nt + nc) * (nt + nc));
				float c = 1. - mix(ddn, dot(tdir, n), float(a > 0.));
				float Re = R0 + (1. - R0) * c * c * c * c * c;
				float P = .25 + .5 * Re;
				float RP = Re / P;
				float TP = (1. - Re) / (1.-P);

				if (rand() < P) { 
					mask *= RP;
				}
				else {
					mask *= obj.color * TP;
					r = Ray(x, tdir);
				}
			}
		}
	}
	return acc;
}

void main() {
	//initSpheres();
	seed = time + resolution.y * gl_FragCoord.x / resolution.x + gl_FragCoord.y / resolution.y;
	vec2 uv = 2. * gl_FragCoord.xy / resolution.xy - 1.;
	//vec3 camPos = vec3((2. * .5* resolution.xy / resolution.xy - 1.) * vec2(48., 40.) + vec2(50., 40.8), 169.);
	vec3 camPos = vec3((2. * (mouse.xy == vec2(0.) ? .5 * resolution.xy : mouse.xy) / resolution.xy - 1.) * vec2(48., 40.) + vec2(50., 40.8), 169.);
	vec3 cz = normalize(vec3(50., 40., 81.6) - camPos);
	vec3 cx = vec3(1., 0., 0.);
	vec3 cy = normalize(cross(cx, cz)); cx = cross(cz, cy);
    
    // Moving average (multipass code)
	vec3 color = texture(channel0, st).rgb * float(frame);
    color += radiance(Ray(camPos, normalize(.53135 * (resolution.x/resolution.y*uv.x * cx - uv.y * cy) + cz)));
	fragColor = vec4(color/float(frame + 1), 1.);
}