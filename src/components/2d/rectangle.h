#pragma once
#include "components/object.h"

class rectangle : public object
{
public:
	bool noFill;

	rectangle(float width, float height);

	void customDraw();
	glm::vec3 getCenter();

private:
	float m_width;
	float m_height;
};
