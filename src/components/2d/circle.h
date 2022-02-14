#pragma once
#include "components/object.h"

class circle : public object
{
public:
	bool noFill;

	circle(float radius);

	void customDraw();
	glm::vec3 getCenter();
	glm::vec3 getBBox();

private:
	float m_radius;
};

