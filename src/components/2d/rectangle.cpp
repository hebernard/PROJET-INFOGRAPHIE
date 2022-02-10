#include "rectangle.h"

rectangle::rectangle(float width, float height) : 
	object(new hierarchyButton(*this, "images/icons/rectangle.png", "Rectangle")), m_width(width), m_height(height), noFill(false)
{
}

void rectangle::customDraw()
{
	ofPushStyle();

	if (noFill) {ofNoFill();}
	else {ofFill();}

	ofDrawRectangle(getPosition(), m_width, m_height);
	ofPopStyle();
}

glm::vec3 rectangle::getCenter()
{
	return getPosition();
}