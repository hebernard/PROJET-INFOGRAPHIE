#include "sphere.h"

sphere::sphere(float radius) : object(new hierarchyButton(*this, "images/icons/sphere.png", "Sphere")), 
	m_radius(radius),
	radiusInput("Radius", m_radius),
	resolutionInput("Resolution", m_resolution),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
	cout << "Sphere added with " << radius << " radius" << endl;
}

void sphere::customDraw()
{
	ofSetSphereResolution(m_resolution);
	ofSetLineWidth(m_contourThickness);
	ofDrawSphere(0, 0, 0, m_radius);
}

void sphere::drawProperties(int x, int y, int width)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	radiusInput.draw(x, offset, width);
	offset += 10 + radiusInput.getHeight();
	resolutionInput.draw(x, offset, width);
	offset += 10 + resolutionInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
}

glm::vec3 sphere::getBBox()
{
	return glm::vec3(m_radius*2, m_radius*2, m_radius*2);
}
