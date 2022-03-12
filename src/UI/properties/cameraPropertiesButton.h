#pragma once
#include "ofRectangle.h"
#include "ofImage.h"

class cameraPropertiesButton
{
public:
	bool isSelected = false;

	cameraPropertiesButton(std::string text, std::string iconPath);
	void draw(int x, int y, int width);

	int getY();

private:
	std::string m_text;
	ofImage icon;
	ofRectangle rect;
};

