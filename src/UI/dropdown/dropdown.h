#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"
#include "dropdownPanel.h"

class label;
class menuBar;

class dropdownTheme : public ofxDatGuiTheme
{
public:
	dropdownTheme()
	{
		layout.height = 40;
		init();
	}
};

class dropdown : public ofxDatGuiToggle
{
public:
	dropdown(int index, std::string text, menuBar& menu);
	void setTheme(const ofxDatGuiTheme* theme);

	void draw();
	void update();

	void addButton(dropdownButton* button);

protected:
	void onMouseRelease(ofPoint m);

private:
	int index;
	bool opened;

	std::string m_text;
	glm::vec2 textSize;

	ofImage downArrow;
	dropdownPanel panel;
	menuBar& m_menu;
	void onToggled(ofxDatGuiToggleEvent e);
};

