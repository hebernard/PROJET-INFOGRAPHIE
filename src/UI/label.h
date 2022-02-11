#pragma once

#include "ofxDatGuiLabel.h"
#include "mainTheme.h"

class label : public ofxDatGuiLabel
{
public:
	label(std::string text, std::string font, int fontSize, ofColor color);
	void draw();

	int getWidth();
	int getHeight();

	void setColor(ofColor color);

private:
	mainTheme& t = t.getInstance();

	ofTrueTypeFont font;
	ofColor color;
};

