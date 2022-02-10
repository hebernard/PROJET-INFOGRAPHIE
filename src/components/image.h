#pragma once

#include "object.h"

class image : public object
{
public:
	image(string path);

	void customDraw();
	void drawHierarchy(int x, int y);

private:
	glm::vec2 size;
	ofImage im;
};

