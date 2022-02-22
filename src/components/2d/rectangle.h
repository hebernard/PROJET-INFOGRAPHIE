#pragma once
#include "components/object.h"

class rectangle : public object
{
public:
	rectangle(float width, float height);

	void customDraw();
	glm::vec3 getBBox();

private:
	float m_width;
	float m_height;
};

