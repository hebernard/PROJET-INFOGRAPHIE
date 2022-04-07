#include "sphere.h"

sphere::sphere(float radius) : object(new hierarchyButton(*this, "images/icons/sphere.png", "Sphere")),
	m_radius(radius),
	radiusInput("Radius", m_radius),
	resolutionInput("Resolution", m_resolution),
	contourThicknessInput("Contour Thickness", m_contourThickness),
	m_emission(),
	m_reflection(),
	m_raytracing(false),
	raytracingTypeProp("Material type")
{
	cout << "Sphere added with " << radius << " radius" << endl;
}

sphere::sphere(float radius, glm::vec3 p, glm::vec3 e, glm::vec3 c, int refl) : sphere(radius)
{
	setPosition(p);
	m_emission = e;
	color = ofColor(c.r * 255, c.g * 255, c.b * 255);
	colorPicker->forceUpdate();
	m_reflection = refl;
	m_raytracing = true;

	raytracingTypeProp.setElements({"Diffuse", "Specular", "Refraction"});
	raytracingTypeProp.setSelected(refl);
	raytracingTypeProp.onClick = [&](int index)
	{
		m_reflection = index;
	};
}

void sphere::customDraw()
{
	ofSetSphereResolution(m_resolution);
	ofSetLineWidth(m_contourThickness);
	ofDrawSphere(0, 0, 0, m_radius);
}

void sphere::drawProperties(int x, int y, int width)
{
	int offset = y;
	if (!m_raytracing)
	{
		object::drawProperties(x, offset, width);
		offset += getPropertiesHeight();

		resolutionInput.draw(x, offset, width);
		offset += 10 + resolutionInput.getHeight();

		contourThicknessInput.draw(x, offset, width);
		offset += 10 + contourThicknessInput.getHeight();
	}
	else
	{
		colorPicker->draw(x, offset, width);
		offset += 10 + colorPicker->getHeight();

		raytracingTypeProp.draw(x, offset, width);
		offset += 10 + raytracingTypeProp.getHeight();
	}

	radiusInput.draw(x, offset, width);
}

glm::vec3 sphere::getBBox()
{
	return glm::vec3(m_radius*2, m_radius*2, m_radius*2);
}

float sphere::getRadius()
{
	return m_radius;
}

glm::vec3 sphere::getEmission()
{
	return m_emission;
}

int sphere::getReflection()
{
	return m_reflection;
}
