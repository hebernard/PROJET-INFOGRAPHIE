#pragma once

#include "object.h"

class sphere : public object
{
public:
	bool noFill;

	sphere(float radius);

	void customDraw();
	glm::vec3 getCenter();

private:
	float m_radius;
};

