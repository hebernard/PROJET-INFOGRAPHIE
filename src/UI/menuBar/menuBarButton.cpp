#include "menuBarButton.h"
#include "label.h"
#include "mainTheme.h"
#include "cursor.h"

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

void menuBarButton::draw(int textOffset)
{
	if (mFocused && mMouseDown)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::color3());
	}
	else if (mMouseOver)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::color2());
	}
	else
	{
		ofSetColor(mainTheme::color1());
	}
	ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

	drawText(x + getWidth() / 2 - textSize.x / 2, y + textSize.y + textOffset, m_text, 11);
}

void menuBarButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}

void menuBarButton::setLabel(std::string text)
{
	m_text = text;
}
