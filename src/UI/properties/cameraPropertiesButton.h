#pragma once
#include "ofRectangle.h"
#include "ofImage.h"

class cameraPropertiesButton
{
public:
	bool isSelected = false;

	cameraPropertiesButton(std::string text, std::string iconPath, bool isDefault, int type);
	void draw(int x, int y, int width);

	int getY();
	void setSelected();
	void setUnselected();
	bool isInside();
	ofRectangle getArea();

private:
	std::string m_text;
	ofImage icon;
	ofRectangle rect;
	bool m_isDefault = false;
	int m_buttonType;
};

