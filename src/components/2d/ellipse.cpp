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
	ofDrawEllipse(0, 0, 0, m_width, m_height);

	ofPopStyle();
}

glm::vec3 ellipse::getCenter()
{
	return getPosition();
}

glm::vec3 ellipse::getBBox()
{
	return glm::vec3(m_width, m_height, 0);
}
