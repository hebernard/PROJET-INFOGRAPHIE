#pragma once

#include "component.h"
#include "ofImage.h"

class ofFileDialogResult;

class image : public component
{
public:
	image(const object& objRef, ofFileDialogResult result);

	void drawUI();
	void draw();

private:
	glm::vec2 size;
	ofImage im;
};

