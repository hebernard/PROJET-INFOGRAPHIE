#pragma once

#include "object.h"
#include "floatInputProperty.h"
#include "checkBoxProperty.h"

class cube : public object
{
public:
	cube(float width, float height, float depth);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	float m_width;
	float m_height;
	float m_depth;
	float m_contourThickness = 1;
	floatInputProperty widthInput;
	floatInputProperty heightInput;
	floatInputProperty depthInput;
	floatInputProperty contourThicknessInput;
};

