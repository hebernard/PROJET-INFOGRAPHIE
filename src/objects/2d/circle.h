#pragma once
#include "objects/object.h"

class circle : public object
{
public:
	circle(float radius);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

private:
	float m_radius;
	float m_resolution = 20;
	float m_contourThickness = 1;
	inputProperty radiusInput;
	inputProperty resolutionInput;
	inputProperty contourThicknessInput;

};

