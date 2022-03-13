#pragma once
#include "ofMain.h"
#include "colorPicker.h"

class colorProperty
{
public:
	colorProperty(std::string label, ofColor& ref);

	void draw(int x, int y, int width);

	int getHeight();

private:
	ofColor& m_ref;
	std::string m_label;
	glm::vec2 textSize;

	ofRectangle colorRect;
	bool showPicker = false;
	colorPicker picker;
};