#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"

class label;

class dropdownTheme : public ofxDatGuiTheme
{
public:
	dropdownTheme()
	{
		layout.height = 40;
		init();
	}
};

class dropdown : public ofxDatGuiButton
{
public:
	dropdown(std::string text);
	void setTheme(const ofxDatGuiTheme* theme);

	void draw();
	void update();
	void setPosition(int x, int y);

private:
	label* mLabel;
	ofImage downArrow;
};

