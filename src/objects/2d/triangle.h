#pragma once
#include "objects/object.h"

class triangle : public object
{
public:
	triangle(int width, int height);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	float m_width;
	float m_height;
	float m_contourThickness = 1;
	inputProperty widthInput;
	inputProperty heightInput;
	inputProperty contourThicknessInput;
};

