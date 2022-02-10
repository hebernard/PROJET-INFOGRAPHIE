#include "cube.h"

cube::cube(float width, float height, float depth)
	: object(new hierarchyButton(*this, "images/icons/cube.png", "Cube")), m_width(width), m_height(height), m_depth(depth), noFill(false)
{
}

void cube::customDraw()
{
	ofPushStyle();
	if (noFill)
	{
		ofNoFill();
	}
	else
	{
		ofFill();
	}
	ofDrawBox(getPosition(), m_width, m_height, m_depth);
	ofPopStyle();
}

glm::vec3 cube::getCenter()
{
	return getPosition();
}