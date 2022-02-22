#include "triangle.h"

triangle::triangle(int width, int height) : 
	object(new hierarchyButton(*this, "images/icons/triangle.png", "Triangle")), m_width(width), m_height(height)
{
}

void triangle::customDraw()
{
	/*
	*    2
	* 1     3
	*/
	ofDrawTriangle(-m_width / 2.f, -m_height / 2.f, 0, 0, m_height / 2.f, 0, m_width / 2.f, -m_height / 2.f, 0);
}

glm::vec3 triangle::getBBox()
{
	return glm::vec3(m_width, m_height, 0);
}