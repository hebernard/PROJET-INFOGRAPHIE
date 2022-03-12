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
	std::string m_text;
	glm::vec2 textSize;

	void setTheme(const ofxDatGuiTheme* theme);
};

