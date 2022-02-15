#pragma once

#include "object.h"

class image : public object
{
public:
	image(string path);

	void customDraw();
	glm::vec3 getCenter();
	glm::vec3 getBBox();

private:
	glm::vec2 size;
	ofImage im;
};

