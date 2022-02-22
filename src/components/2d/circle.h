#pragma once
#include "components/object.h"
#include "floatInputProperty.h"

class circle : public object
{
public:
	bool noFill;

	circle(float radius);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	float m_radius;
	floatInputProperty radiusInput;
};

