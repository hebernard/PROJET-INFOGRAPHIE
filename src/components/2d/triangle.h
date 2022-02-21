#pragma once
#include "components/object.h"

class triangle : public object
{
public:
	bool noFill;

	triangle(int width, int height);

	void customDraw();
	glm::vec3 getCenter();
	glm::vec3 getBBox();

private:
	int m_width;
	int m_height;
};

