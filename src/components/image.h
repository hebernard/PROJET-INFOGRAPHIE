#pragma once

#include "ofMain.h"

class image : public ofNode
{
public:
	image(string path);

	void customDraw();

private:
	glm::vec2 size;
	ofImage im;
};

