#pragma once
#include "components/object.h"

class triangle : public object
{
public:
	bool noFill;

	triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	void customDraw();
	glm::vec3 getCenter();

private:
	glm::vec3 m_p1;
	glm::vec3 m_p2;
	glm::vec3 m_p3;
};

