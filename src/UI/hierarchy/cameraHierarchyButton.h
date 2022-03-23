#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"
#include "hierarchySmallButton.h"

class cameraHierarchyButton : public ofxDatGuiButton
{
public:
	hierarchySmallButton* propertiesButton;

	cameraHierarchyButton(std::string iconPath, std::string text);
	~cameraHierarchyButton();

	void draw();
	void update(int x, int y);
	std::string getLabel();

private:
	std::string m_text;
	glm::vec2 textSize;
	ofImage icon;

	hierarchySmallButton* addCameraButton;
	hierarchySmallButton* removeCameraButton;

	void setTheme(const ofxDatGuiTheme* theme);
};

