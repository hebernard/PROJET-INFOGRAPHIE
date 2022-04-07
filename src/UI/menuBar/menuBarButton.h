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

	void draw(int textOffset);
	void update(int x, int y);

	void setLabel(std::string text);

protected:
	void onMouseRelease(ofPoint m);

private:
	std::string m_text;
	glm::vec2 textSize;

	void setTheme(const ofxDatGuiTheme* theme);
};

