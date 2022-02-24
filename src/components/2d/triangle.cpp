#include "triangle.h"

triangle::triangle(int width, int height) : 
	object(new hierarchyButton(*this, "images/icons/triangle.png", "Triangle")), 
	m_width(width), m_height(height),
	widthInput("Width", m_width),
	heightInput("Height", m_height),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
}

void triangle::customDraw()
{
	ofSetLineWidth(m_contourThickness);
	/*
	*    2
	* 1     3
	*/
	ofDrawTriangle(-m_width / 2.f, -m_height / 2.f, 0, 0, m_height / 2.f, 0, m_width / 2.f, -m_height / 2.f, 0);
}

void triangle::drawProperties(int x, int y, int width)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	widthInput.draw(x, offset, width);
	offset += 10 + widthInput.getHeight();
	heightInput.draw(x, offset, width);
	offset += 10 + heightInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
}

glm::vec3 triangle::getBBox()
{
	return glm::vec3(m_width, m_height, 0);
}