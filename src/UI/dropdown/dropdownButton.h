#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"

class label;

class dropdownButtonTheme : public ofxDatGuiTheme
{
public:
	dropdownButtonTheme()
	{
		layout.width = 250;
		layout.height = 40;
		init();
	}
};

class dropdownButton : public ofxDatGuiButton
{
public:
	dropdownButton(std::string iconPath, std::string text);

	void draw();
	void update(int x, int y);

private:
	std::string m_text;
	glm::vec2 textSize;
	ofImage icon;

	void setTheme(const ofxDatGuiTheme* theme);
};

