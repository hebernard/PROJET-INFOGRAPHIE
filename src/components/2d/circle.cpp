#include "circle.h"

circle::circle(float radius) : 
	object(new hierarchyButton(*this, "images/icons/circle.png", "Circle")), 
	m_radius(radius), 
	radiusInput("Radius", m_radius)
{
}

void circle::customDraw()
{
	ofDrawCircle(0, 0, 0, m_radius);
}

void circle::drawProperties(int x, int y, int width)
{
	object::drawProperties(x, y, width);
	radiusInput.draw(x, y + getPropertiesHeight(), width);
}

glm::vec3 circle::getBBox()
{
	return glm::vec3(m_radius * 2, m_radius * 2, 0);
}
