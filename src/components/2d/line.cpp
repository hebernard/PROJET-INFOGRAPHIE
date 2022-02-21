#include "line.h"

line::line(int length)
	: object(new hierarchyButton(*this, "images/icons/line.png", "Line")), m_length(length)
{
}

void line::customDraw()
{
	ofDrawLine(-m_length / 2, 0, 0, m_length / 2, 0, 0);
}

glm::vec3 line::getCenter()
{
	// The position is the center since the line is drawn
	// from its center point from the customDraw() method
	return getPosition();
}

glm::vec3 line::getBBox()
{
	// No point on drawing the bounding box for the line
	return glm::vec3(0, 0, 0);
}
