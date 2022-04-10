#include "circle.h"

circle::circle(float radius) : 
	object(new hierarchyButton(*this, "images/icons/circle.png", "Circle")), 
	m_radius(radius), 
	radiusInput("Radius", m_radius),
	resolutionInput("Resolution", m_resolution),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
	canHaveMaterial = false;
}

void circle::customDraw()
{
	ofSetCircleResolution(m_resolution);
	ofSetLineWidth(m_contourThickness);
	ofDrawCircle(0, 0, 0, m_radius);
}

void circle::drawProperties(int x, int y, int width, int originX, int originY)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	colorPicker->draw(x, offset, width);
	offset += 10 + colorPicker->getHeight();
	radiusInput.draw(x, offset, width);
	offset += 10 + radiusInput.getHeight();
	resolutionInput.draw(x, offset, width);
	offset += 10 + resolutionInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
}

glm::vec3 circle::getBBox()
{
	return glm::vec3(m_radius * 2, m_radius * 2, 0);
}

