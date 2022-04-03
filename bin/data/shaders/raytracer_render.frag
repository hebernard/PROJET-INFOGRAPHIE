#version 330

uniform sampler2D channel0;

in vec2 st;

out vec4 fragColor;

void main() {
	vec3 color = texture(channel0, st).rgb;
	fragColor = vec4(pow(clamp(color, 0., 1.), vec3(1./2.2)), 1.);
}