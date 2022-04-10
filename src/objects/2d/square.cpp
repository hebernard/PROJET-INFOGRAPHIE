#include "square.h"

square::square(float size) :
	object(new hierarchyButton(*this, "images/icons/square.png", "Square")), 
	m_size(size),
	sizeInput("Size", m_size),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
	canHaveMaterial = false;
}

void square::customDraw()
{
	ofSetLineWidth(m_contourThickness);
	ofDrawRectangle(-m_size/2, -m_size / 2, 0, m_size, m_size);
}

void square::drawProperties(int x, int y, int width, int originX, int originY)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	colorPicker->draw(x, offset, width);
	offset += 10 + colorPicker->getHeight();
	sizeInput.draw(x, offset, width);
	offset += 10 + sizeInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
	offset += 10 + contourThicknessInput.getHeight();

}

glm::vec3 square::getBBox()
{
	return glm::vec3(m_size, m_size, 0);
}