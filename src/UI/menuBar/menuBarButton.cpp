#include "menuBarButton.h"
#include "label.h"
#include "mainTheme.h"

menuBarButton::menuBarButton(std::string text) : ofxDatGuiButton(text), m_text(text)
{
	setTheme(new menuBarButtonTheme());
	textSize = label::getSize(text, 11);
}

void menuBarButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void menuBarButton::draw()
{
	if (mFocused && mMouseDown)
	{
		ofSetColor(mainTheme::color3());
	}
	else if (mMouseOver)
	{
		ofSetColor(mainTheme::color2());
	}
	else
	{
		ofSetColor(mainTheme::color1());
	}
	ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

	drawText(x + getWidth() / 2 - textSize.x / 2, y + textSize.y + 10, m_text, 11);
}

void menuBarButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}
