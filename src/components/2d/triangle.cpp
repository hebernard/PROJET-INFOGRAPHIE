#include "triangle.h"

triangle::triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) : 
	object(new hierarchyButton(*this, "images/icons/triangle.png", "Triangle")), m_p1(p1), m_p2(p2), m_p3(p3), noFill(false)
{
}

void triangle::customDraw()
{
	ofPushStyle();

	if (noFill) { ofNoFill(); }
	else { ofFill(); }

	ofDrawTriangle(m_p1, m_p2, m_p3);
	ofPopStyle();
}

glm::vec3 triangle::getCenter()
{
	glm::vec3 position((getPosition().x + m_p3.x) / 2, (getPosition().y + m_p2.y) / 2, getPosition().z);
	return position;
}

glm::vec3 triangle::getBBox()
{
	return glm::vec3((m_p1.x+m_p3.x)/2, m_p2.y/2, 0);
}