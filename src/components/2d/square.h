#pragma once
#include "components/object.h"

class square : public object
{
public:
	bool noFill;

	square(float size);

	void customDraw();
	glm::vec3 getCenter();

private:
	float m_size;
};

