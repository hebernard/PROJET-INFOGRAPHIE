#pragma once
#include "objects/object.h"
#include "ui/properties/sliders/sliderProperty.h"

class ellipse : public object
{
public:
	ellipse(float width, float height);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

private:
	float m_width;
	float m_height;
	int m_resolution = 20;
	float m_contourThickness = 1;
	inputProperty widthInput;
	inputProperty heightInput;
	sliderProperty resolutionInput;
	inputProperty contourThicknessInput;
};

