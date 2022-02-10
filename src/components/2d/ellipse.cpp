#include "ellipse.h"

ellipse::ellipse(float width, float height) 
	: object(new hierarchyButton(*this, "images/icons/ellipse.png", "Ellipse")), m_width(width), m_height(height), noFill(false)
{
}

void ellipse::customDraw()
{
	ofPushStyle();

	if (noFill) { ofNoFill(); }
	else { ofFill(); }

	ofSetCircleResolution(50);
	ofDrawEllipse(getPosition(), m_width, m_height);
	ofPopStyle();
}

glm::vec3 ellipse::getCenter()
{
	return getPosition();
}