#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"
#include "hierarchySmallButton.h"

class object;

class hierarchyButtonTheme : public ofxDatGuiTheme
{
public:
	hierarchyButtonTheme()
	{
		layout.width = 300;
		layout.height = 30;
		init();
	}
};

class hierarchyButton : public ofxDatGuiButton
{
public:
	bool isInteractable = true;

	hierarchyButton(object& obj, std::string iconPath, std::string text);
	virtual ~hierarchyButton();

	virtual void draw();
	virtual void update(int x, int y);
	std::string getLabel();

protected:
	std::string m_text;
	glm::vec2 textSize;
	ofImage icon;
	object& m_obj;

	hierarchySmallButton* deleteButton;
	hierarchySmallButton* propertiesButton;
	hierarchySmallButton* visibleButton;

	void setTheme(const ofxDatGuiTheme* theme);
	void onClick(ofxDatGuiButtonEvent e);

	void drawMain();
	void drawButtons();
};

