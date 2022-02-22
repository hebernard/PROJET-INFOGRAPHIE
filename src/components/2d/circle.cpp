#include "circle.h"

circle::circle(float radius) : 
	object(new hierarchyButton(*this, "images/icons/circle.png", "Circle")), 
	m_radius(radius), 
	noFill(false),
	radiusInput("Radius", m_radius)
{
}

void circle::customDraw()
{
	ofPushStyle();

	if (noFill) { ofNoFill(); }
	else { ofFill(); }

	ofSetCircleResolution(50);
	ofDrawCircle(0, 0, 0, m_radius);
	ofPopStyle();
}

void circle::drawProperties(int x, int y, int width)
{
	radiusInput.draw(x, y, width);
}

glm::vec3 circle::getBBox()
{
	return glm::vec3(m_radius * 2, m_radius * 2, 0);
}
