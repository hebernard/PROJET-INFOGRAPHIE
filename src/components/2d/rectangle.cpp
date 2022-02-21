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

	ofDrawRectangle(-m_width / 2, -m_height / 2, 0, m_width, m_height);

	ofPopStyle();
}

glm::vec3 rectangle::getBBox()
{
	return glm::vec3(m_width, m_height, 0);
}