#include "circle.h"

circle::circle(float radius) : object(new hierarchyButton(*this, "images/icons/circle.png", "Circle")), m_radius(radius), noFill(false)
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

glm::vec3 circle::getCenter()
{
	return getPosition();
}

glm::vec3 circle::getBBox()
{
	return glm::vec3(m_radius * 2, m_radius * 2, 0);
}
