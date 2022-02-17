#include "cube.h"

cube::cube(float width, float height, float depth)
	: object(new hierarchyButton(*this, "images/icons/cube.png", "Cube")), m_width(width), m_height(height), m_depth(depth), noFill(false)
{
}

void cube::customDraw()
{
	ofPushMatrix();
	ofPushStyle();
	if (noFill)
	{
		ofNoFill();
	}
	else
	{
		ofFill();
	}

	ofTranslate(getPosition());
	ofRotateXDeg(getOrientationEulerDeg().x);
	ofRotateYDeg(getOrientationEulerDeg().y);
	ofRotateZDeg(getOrientationEulerDeg().z);

	ofDrawBox(0, 0, 0, m_width, m_height, m_depth);
	ofPopStyle();
	ofPopMatrix();
}

glm::vec3 cube::getCenter()
{
	return getPosition();
}

glm::vec3 cube::getBBox()
{
	return glm::vec3(m_width, m_height, m_depth);
}
