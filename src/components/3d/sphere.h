#pragma once

#include "object.h"
#include "floatInputProperty.h"
#include "checkBoxProperty.h"

class sphere : public object
{
public:
	sphere(float radius);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	float m_radius;
	float m_resolution = 50;
	float m_contourThickness = 1;
	floatInputProperty radiusInput;
	floatInputProperty resolutionInput;
	floatInputProperty contourThicknessInput;
};

