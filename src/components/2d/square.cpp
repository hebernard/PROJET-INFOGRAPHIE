#include "square.h"

square::square(float size) :
	object(new hierarchyButton(*this, "images/icons/square.png", "Square")), m_size(size)
{
}

void square::customDraw()
{
	ofDrawRectangle(-m_size/2, -m_size / 2, 0, m_size, m_size);
}

glm::vec3 square::getBBox()
{
	return glm::vec3(m_size, m_size, 0);
}