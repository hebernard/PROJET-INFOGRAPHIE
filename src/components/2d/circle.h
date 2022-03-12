#pragma once
#include "components/object.h"
#include "inputProperty.h"
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
	float m_resolution = 20;
	float m_contourThickness = 1;
	inputProperty radiusInput;
	inputProperty resolutionInput;
	inputProperty contourThicknessInput;

};

