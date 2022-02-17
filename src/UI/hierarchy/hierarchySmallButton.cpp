#include "hierarchySmallButton.h"
#include "mainTheme.h"
#include "cursor.h"

hierarchySmallButton::hierarchySmallButton(std::string iconPath) : ofxDatGuiButton("hierarchySmallButton")
{
	changeIcon(iconPath);

	setTheme(new hierarchySmallButtonTheme());
}

void hierarchySmallButton::draw()
{
	ofPushStyle();

	if (mMouseOver)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::toolBarButtonHoverColor());
		ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);
	}

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(x + getWidth() / 2 - icon.getWidth() / 2, y + getHeight() / 2 - icon.getHeight() / 2);
	}
	ofPopStyle();
}

void hierarchySmallButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}

void hierarchySmallButton::changeIcon(std::string path)
{
	icon.load(path);
	icon.resize(22, 22);
}

void hierarchySmallButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}
