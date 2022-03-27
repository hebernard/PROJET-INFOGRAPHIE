#include "rectangle.h"

rectangle::rectangle(float width, float height) : 
	object(new hierarchyButton(*this, "images/icons/rectangle.png", "Rectangle")), 
	m_width(width), m_height(height),
	widthInput("Width", m_width),
	heightInput("Height", m_height),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
	canHaveMaterial = false;
}

void rectangle::customDraw()
{
	ofSetLineWidth(m_contourThickness);
	ofDrawRectangle(-m_width / 2, -m_height / 2, 0, m_width, m_height);
}

void rectangle::drawProperties(int x, int y, int width)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	colorPicker->draw(x, offset, width);
	offset += 10 + colorPicker->getHeight();
	widthInput.draw(x, offset, width);
	offset += 10 + widthInput.getHeight();
	heightInput.draw(x, offset, width);
	offset += 10 + heightInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
}

glm::vec3 rectangle::getBBox()
{
	return glm::vec3(m_width, m_height, 0);
}