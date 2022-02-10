#include "line.h"

line::line(glm::vec3 p1, glm::vec3 p2)
	: object(new hierarchyButton(*this, "images/icons/line.png", "Line")), m_p1(p1), m_p2(p2), noFill(false)
{
}

void line::customDraw()
{
	ofPushStyle();

	if (noFill) { ofNoFill(); }
	else { ofFill(); }

	ofDrawLine(m_p1, m_p2);
	ofPopStyle();
}

glm::vec3 line::getCenter()
{
	return getPosition();
}