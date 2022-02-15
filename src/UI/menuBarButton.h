#pragma once

#include "ofxDatGuiButton.h"

class label;

class menuBarButtonTheme : public ofxDatGuiTheme
{
public:
	menuBarButtonTheme()
	{
		layout.width = 80;
		layout.height = 38;
		init();
	}
};

class menuBarButton : public ofxDatGuiButton
{
public:
	menuBarButton(std::string text);

	void draw();
	void update(int x, int y);

private:

	label* m_label;

	void setTheme(const ofxDatGuiTheme* theme);
};

