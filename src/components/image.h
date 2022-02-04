#pragma once

#include "ofNode.h"
#include "ofImage.h"

class image : public ofNode
{
public:
	image(std::string path);

	void drawUI();
	void customDraw();

private:
	glm::vec2 size;
	ofImage im;
};

