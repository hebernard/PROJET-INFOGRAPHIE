#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"

class hierarchySmallButton;

class cameraHierarchyButton : public ofxDatGuiButton
{
public:
	cameraHierarchyButton(std::string iconPath, std::string text);

	void draw();
	void update(int x, int y);
	std::string getLabel();

private:
	std::string m_text;
	glm::vec2 textSize;
	ofImage icon;

	hierarchySmallButton* propertiesButton;

	void setTheme(const ofxDatGuiTheme* theme);
};

