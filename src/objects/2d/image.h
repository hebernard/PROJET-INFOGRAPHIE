#pragma once
#include "objects/object.h"

class image : public object
{
public:
	image(string path);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

private:
	ofImage im;

	float width;
	float height;
	inputProperty widthInput;
	inputProperty heightInput;
};

