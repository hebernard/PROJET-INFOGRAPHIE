#include "menuBarButton.h"
#include "label.h"

menuBarButton::menuBarButton(std::string text) : ofxDatGuiButton(text), m_label(new label(text, t.fontMediumPath, 11, t.fontColor))
{
	setTheme(new menuBarButtonTheme());
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
		ofSetColor(t.color3);
	}
	else if (mMouseOver)
	{
		ofSetColor(t.color2);
	}
	else
	{
		ofSetColor(t.color1);
	}
	ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

	m_label->setPosition(x + getWidth() / 2 - m_label->getWidth() / 2, y + m_label->getHeight() + 10);
	m_label->setColor(t.fontColor);
	m_label->draw();
}

void menuBarButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}
