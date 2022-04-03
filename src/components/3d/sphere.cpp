#include "sphere.h"

sphere::sphere(float radius) : object(new hierarchyButton(*this, "images/icons/sphere.png", "Sphere")),
	m_radius(radius),
	radiusInput("Radius", m_radius),
	resolutionInput("Resolution", m_resolution),
	contourThicknessInput("Contour Thickness", m_contourThickness),
	m_emission(),
	m_raytracingColor(),
	m_reflection(),
	m_raytracing(false)
{
	cout << "Sphere added with " << radius << " radius" << endl;
}

sphere::sphere(float radius, glm::vec3 p, glm::vec3 e, glm::vec3 c, int refl) : sphere(radius)
{
	setPosition(p);
	m_emission = e;
	m_raytracingColor = c;
	m_reflection = refl;
	m_raytracing = true;
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

glm::vec3 sphere::getRaytracingColor()
{
	return m_raytracingColor;
}

int sphere::getReflection()
{
	return m_reflection;
}
