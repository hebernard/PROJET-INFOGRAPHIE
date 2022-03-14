#include "line.h"

line::line(int length)
	: object(new hierarchyButton(*this, "images/icons/line.png", "Line")),
	m_length(length),
	lengthInput("Length", m_length),
	contourThicknessInput("Contour Thickness", m_contourThickness)
{
}

void line::customDraw()
{
	ofSetLineWidth(m_contourThickness);
	ofDrawLine(-m_length / 2.f, 0, 0, m_length / 2.f, 0, 0);
}

glm::vec3 line::getBBox()
{
	// No point on drawing the bounding box for the line
	return glm::vec3(0, 0, 0);
}

void line::drawProperties(int x, int y, int width)
{
	// Dont call base class to not set filled property
	int offset = y;
	colorPicker->draw(x, offset, width);
	offset += 10 + colorPicker->getHeight();

	lengthInput.draw(x, offset, width);
	offset += 10 + lengthInput.getHeight();

	contourThicknessInput.draw(x, offset, width);
	offset += 10 + contourThicknessInput.getHeight();
}
