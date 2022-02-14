#pragma once
#include "components/object.h"

class ellipse : public object
{
public:
	bool noFill;

	ellipse(float width, float height);

	void customDraw();
	glm::vec3 getCenter();
	glm::vec3 getBBox();

private:
	float m_width;
	float m_height;
};

