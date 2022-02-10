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
	ofDrawCircle(getPosition(), m_radius);
	ofPopStyle();
}

glm::vec3 circle::getCenter()
{
	return getPosition();
}
