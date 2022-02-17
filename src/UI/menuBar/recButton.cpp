#include "recButton.h"
#include "label.h"
#include "mainTheme.h"
#include "cursor.h"

recButton::recButton(std::string iconPath) : ofxDatGuiButton("recButton"), icon()
{
	icon.load(iconPath);
	icon.resize(22, 22);
	recMode = false;
	setTheme(new recButtonTheme());
}

void recButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void recButton::draw()
{
	ofPushStyle();
	ofFill();
	ofSetCircleResolution(100);

	if (!recMode) {
		if (mFocused && mMouseDown)
		{
			ofSetColor(mainTheme::fontColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 20);

			ofSetColor(mainTheme::recColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 2);
		}
		else if (mMouseOver)
		{
			ofSetColor(mainTheme::fontColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 20);

			ofSetColor(mainTheme::recColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 6);
		}
		else
		{
			ofSetColor(mainTheme::fontColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 20);

			ofSetColor(mainTheme::recColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 5);
		}
	}
	else {
		if (mFocused && mMouseDown)
		{
			ofSetColor(mainTheme::fontColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 20);

			ofSetColor(mainTheme::recColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 18);
		}
		else if (mMouseOver)
		{
			ofSetColor(mainTheme::fontColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight()/2, 20);

			ofSetColor(mainTheme::recColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 14);
		}
		else
		{
			ofSetColor(mainTheme::fontColor());
			ofDrawCircle(ofGetWidth()/2, y + getHeight() / 2, 20);

			ofSetColor(mainTheme::recColor());
			ofDrawCircle(ofGetWidth() / 2, y + getHeight() / 2, 15);
		}
	}
	
	ofPopStyle();
}

void recButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}

void recButton::updateIcon(std::string iconPath)
{
	icon.load(iconPath);
	icon.resize(22, 22);
}

void recButton::rec()
{
	recMode = !recMode;
}
