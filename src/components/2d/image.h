#pragma once

#include "object.h"

class image : public object
{
public:
	image(string path);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	ofImage im;

	float width;
	float height;
	inputProperty widthInput;
	inputProperty heightInput;
};

