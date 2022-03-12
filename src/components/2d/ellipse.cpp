#include "ellipse.h"

ellipse::ellipse(float width, float height) 
	: object(new hierarchyButton(*this, "images/icons/ellipse.png", "Ellipse")), 
	m_width(width), m_height(height), 
	widthInput("Width", m_width),
	heightInput("Height", m_height),
	resolutionInput("Resolution", m_resolution),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
}

void ellipse::customDraw()
{
	ofSetCircleResolution(m_resolution);
	ofSetLineWidth(m_contourThickness);
	ofDrawEllipse(0, 0, 0, m_width, m_height);
}

void ellipse::drawProperties(int x, int y, int width)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	widthInput.draw(x, offset, width);
	offset += 10 + widthInput.getHeight();
	heightInput.draw(x, offset, width);
	offset += 10 + heightInput.getHeight();
	resolutionInput.draw(x, offset, width);
	offset += 10 + resolutionInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
}

glm::vec3 ellipse::getBBox()
{
	return glm::vec3(m_width, m_height, 0);
}
