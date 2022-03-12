#include "cube.h"

cube::cube(float width, float height, float depth)
	: object(new hierarchyButton(*this, "images/icons/cube.png", "Cube")), 
	m_width(width), m_height(height), m_depth(depth),
	widthInput("Width", m_width),
	heightInput("Height", m_height),
	depthInput("Depth", m_depth),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
}

void cube::customDraw()
{
	ofSetLineWidth(m_contourThickness);
	ofDrawBox(0, 0, 0, m_width, m_height, m_depth);
}

void cube::drawProperties(int x, int y, int width)
{
	int offset = y + getPropertiesHeight();
	object::drawProperties(x, y, width);
	widthInput.draw(x, offset, width);
	offset += 10 + widthInput.getHeight();
	heightInput.draw(x, offset, width);
	offset += 10 + heightInput.getHeight();
	depthInput.draw(x, offset, width);
	offset += 10 + depthInput.getHeight();
	contourThicknessInput.draw(x, offset, width);
}

glm::vec3 cube::getBBox()
{
	return glm::vec3(m_width, m_height, m_depth);
}
