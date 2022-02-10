#include "square.h"

square::square(float size) :
	object(new hierarchyButton(*this, "images/icons/square.png", "Square")), m_size(size), noFill(false)
{
}

void square::customDraw()
{
	ofPushStyle();

	if (noFill) { ofNoFill(); }
	else { ofFill(); }

	ofDrawRectangle(getPosition(), m_size, m_size);
	ofPopStyle();
}

glm::vec3 square::getCenter()
{
	return getPosition();
}