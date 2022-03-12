#include "menuBarButtonAlt.h"
#include "label.h"
#include "mainTheme.h"
#include "cursor.h"

menuBarButtonAlt::menuBarButtonAlt(std::string iconPath) : ofxDatGuiButton("menuBarButtonAlt"), icon()
{
	icon.load(iconPath);
	icon.resize(22, 22);
	setTheme(new menuBarButtonAltTheme());
}

void menuBarButtonAlt::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void menuBarButtonAlt::draw()
{
	ofPushStyle();
	ofFill();

	if (mFocused && mMouseDown)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::logoTopLayerColor());
		ofDrawRectRounded(x, y, 34, 34, 6);

		ofSetColor(ofColor::white);
		icon.draw(x + getWidth() / 2 - icon.getWidth() / 2 + 1, y + getHeight() / 2 - icon.getHeight() / 2 + 2);
	}
	else if (mMouseOver)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::logoDownLayerColor());
		ofDrawRectRounded(x, y, 34, 34, 6);

		ofSetColor(mainTheme::logoTopLayerColor());
		ofDrawRectRounded(x, y - 3, 34, 34, 6);

		ofSetColor(ofColor::white);
		icon.draw(x + getWidth() / 2 - icon.getWidth() / 2 + 1, y + getHeight() / 2 - icon.getHeight() / 2 - 1);
	}
	else
	{
		ofSetColor(mainTheme::logoDownLayerColor());
		ofDrawRectRounded(x, y, 34, 34, 6);

		ofSetColor(mainTheme::logoTopLayerColor());
		ofDrawRectRounded(x, y - 2, 34, 34, 6);

		ofSetColor(ofColor::white);
		icon.draw(x + getWidth() / 2 - icon.getWidth() / 2 + 1, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	ofPopStyle();
}

void menuBarButtonAlt::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}

void menuBarButtonAlt::updateIcon(std::string iconPath)
{
	icon.load(iconPath);
	icon.resize(22, 22);
}