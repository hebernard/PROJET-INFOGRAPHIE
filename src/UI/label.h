#pragma once

#include "ofxDatGuiLabel.h"

class label : public ofxDatGuiLabel
{
public:
	label(std::string text, std::string font, int fontSize, ofColor color);
	void draw();

	int getWidth();
	int getHeight();

	void setColor(ofColor color);

private:
	ofTrueTypeFont font;
	ofColor color;
};
