#include "cube.h"

cube::cube(float width, float height, float depth)
	: object(new hierarchyButton(*this, "images/icons/cube.png", "Cube")), m_width(width), m_height(height), m_depth(depth)
{
}

void cube::customDraw()
{
	ofDrawBox(0, 0, 0, m_width, m_height, m_depth);
}

glm::vec3 cube::getBBox()
{
	return glm::vec3(m_width, m_height, m_depth);
}
