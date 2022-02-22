#pragma once

#include "object.h"

class sphere : public object
{
public:
	sphere(float radius);

	void customDraw();
	glm::vec3 getBBox();

private:
	float m_radius;
};

