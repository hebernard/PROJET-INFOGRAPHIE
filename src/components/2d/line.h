#pragma once
#include "components/object.h"
#include "inputProperty.h"
#include "checkBoxProperty.h"

class line : public object
{
public:
	line(int length);

	void customDraw();
	glm::vec3 getBBox();
	void drawProperties(int x, int y, int width);

private:
	float m_length;
	float m_contourThickness = 1;
	inputProperty lengthInput;
	inputProperty contourThicknessInput;
};

