#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"

class object;
class hierarchySmallButton;

class hierarchyButtonTheme : public ofxDatGuiTheme
{
public:
	hierarchyButtonTheme()
	{
		layout.width = 300;
		layout.height = 40;
		init();
	}
};

class hierarchyButton : public ofxDatGuiButton
{
public:
	hierarchyButton(object& obj, std::string iconPath, std::string text);
	~hierarchyButton();

	void draw();
	void update(int x, int y);
	std::string getLabel();

private:
	std::string m_text;
	glm::vec2 textSize;
	ofImage icon;
	object& m_obj;

	hierarchySmallButton* deleteButton;
	hierarchySmallButton* propertiesButton;
	hierarchySmallButton* visibleButton;

	void setTheme(const ofxDatGuiTheme* theme);
	void onClick(ofxDatGuiButtonEvent e);
};

