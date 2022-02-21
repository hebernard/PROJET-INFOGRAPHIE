#pragma once
#include "components/object.h"

class line : public object
{
public:
	line(int length);

	void customDraw();
	glm::vec3 getBBox();

private:
	int m_length;
};

