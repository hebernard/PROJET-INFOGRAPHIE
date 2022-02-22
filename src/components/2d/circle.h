#pragma once
#include "components/object.h"
#include "floatInputProperty.h"
#include "checkBoxProperty.h"

class circle : public object
{
public:
	circle(float radius);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	float m_radius;
	floatInputProperty radiusInput;
};

