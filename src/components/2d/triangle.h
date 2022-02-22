#pragma once
#include "components/object.h"

class triangle : public object
{
public:
	triangle(int width, int height);

	void customDraw();
	glm::vec3 getBBox();

private:
	int m_width;
	int m_height;
};

