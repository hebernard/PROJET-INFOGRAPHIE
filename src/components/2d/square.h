#pragma once
#include "components/object.h"

class square : public object
{
public:
	square(float size);

	void customDraw();
	glm::vec3 getBBox();

private:
	float m_size;
};

