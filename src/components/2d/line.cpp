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
	glm::vec3 position((getPosition().x + m_p2.x) / 2, (getPosition().y + m_p2.y) / 2, getPosition().z);
	return position;
}

glm::vec3 line::getBBox()
{
	glm::vec3 position(abs(m_p2.x - m_p1.x), abs(m_p2.y - m_p1.y), 0);
	return position;
}
