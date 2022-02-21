#pragma once

#include "object.h"

class image : public object
{
public:
	glm::vec2 size;
	image(string path);

	void customDraw();
	glm::vec3 getBBox();

private:
	ofImage im;
};

