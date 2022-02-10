#pragma once

#include "object.h"

class cube : public object
{
public:
	bool noFill;

	cube(float width, float height, float depth);

	void customDraw();
	glm::vec3 getCenter();

private:
	float m_width;
	float m_height;
	float m_depth;
};

