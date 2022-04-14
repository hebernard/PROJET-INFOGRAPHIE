#pragma once
#include "objects/object.h"
#include "ui/properties/sliders/sliderProperty.h"

class circle : public object
{
public:
	circle(float radius);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

private:
	float m_radius;
	int m_resolution = 20;
	float m_contourThickness = 1;
	inputProperty radiusInput;
	sliderProperty resolutionInput;
	inputProperty contourThicknessInput;

};

