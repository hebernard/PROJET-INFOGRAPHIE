#pragma once
#include "objects/object.h"

class line : public object
{
public:
	line(int length);

	void customDraw();
	glm::vec3 getBBox();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);

private:
	float m_length;
	float m_contourThickness = 1;
	inputProperty lengthInput;
	inputProperty contourThicknessInput;
};

