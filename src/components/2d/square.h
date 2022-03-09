#pragma once
#include "components/object.h"
#include "inputProperty.h"
#include "checkBoxProperty.h"

class square : public object
{
public:
	square(float size);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	float m_size;
	float m_contourThickness = 1;
	inputProperty sizeInput;
	inputProperty contourThicknessInput;
};

