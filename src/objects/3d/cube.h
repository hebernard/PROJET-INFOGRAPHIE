#pragma once

#include "objects/object.h"

class cube : public object
{
public:
	cube(float width, float height, float depth);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

private:
	float m_width;
	float m_height;
	float m_depth;
	float m_contourThickness = 1;
	inputProperty widthInput;
	inputProperty heightInput;
	inputProperty depthInput;
	inputProperty contourThicknessInput;
};

