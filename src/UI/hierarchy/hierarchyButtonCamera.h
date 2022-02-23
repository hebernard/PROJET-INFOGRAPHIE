#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"

class camera;
class hierarchySmallButton;

class hierarchyButtonCameraTheme : public ofxDatGuiTheme
{
public:
	hierarchyButtonCameraTheme()
	{
		layout.width = 300;
		layout.height = 40;
		init();
	}
};

class hierarchyButtonCamera : public ofxDatGuiButton
{
public:
	hierarchyButtonCamera(camera& cam, std::string iconPath, std::string text);

	void draw();
	void update(int x, int y);
	std::string getLabel();

private:
	std::string m_text;
	glm::vec2 textSize;
	ofImage icon;
	camera& m_cam;

	hierarchySmallButton* deleteButton;
	hierarchySmallButton* propertiesButton;
	hierarchySmallButton* visibleButton;

	void setTheme(const ofxDatGuiTheme* theme);
	void onClick(ofxDatGuiButtonEvent e);
};


