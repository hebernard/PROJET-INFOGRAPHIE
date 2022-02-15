#pragma once
#include "components/object.h"

class line : public object
{
public:
	bool noFill;

	line(glm::vec3 p1, glm::vec3 p2);

	void customDraw();
	glm::vec3 getCenter();
	glm::vec3 getBBox();

private:
	glm::vec3 m_p1;
	glm::vec3 m_p2;
};

