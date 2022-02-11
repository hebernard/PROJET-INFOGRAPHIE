#include "menuBarButtonAlt.h"
#include "label.h"

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
		ofSetColor(t.logoTopLayerColor);
		ofDrawRectRounded(x, y, 34, 34, 6);

		ofSetColor(ofColor::white);
		icon.draw(ofGetWidth() - this->getWidth() * 2 + 7, this->getHeight() - 4);
	}
	else if (mMouseOver)
	{
		ofSetColor(t.logoDownLayerColor);
		ofDrawRectRounded(x, y, 34, 34, 6);

		ofSetColor(t.logoTopLayerColor);
		ofDrawRectRounded(x, y - 3, 34, 34, 6);

		ofSetColor(ofColor::white);
		icon.draw(ofGetWidth() - this->getWidth() * 2 + 7, this->getHeight() - 7);
	}
	else
	{
		ofSetColor(t.logoDownLayerColor);
		ofDrawRectRounded(x, y, 34, 34, 6);

		ofSetColor(t.logoTopLayerColor);
		ofDrawRectRounded(x, y - 2, 34, 34, 6);

		ofSetColor(ofColor::white);
		icon.draw(ofGetWidth() - this->getWidth() * 2 + 7, this->getHeight() - 6);
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