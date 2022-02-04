#include "menuBarButton.h"
#include "label.h"

menuBarButton::menuBarButton(std::string text) : ofxDatGuiButton(text), m_label(new label(text, "fonts/inter_regular.ttf", 11, ofColor::white))
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
		ofSetColor(ofColor(87, 140, 245));
	}
	else if (mMouseOver)
	{
		ofSetColor(ofColor(115, 157, 247));
	}
	else
	{
		ofSetColor(ofColor(58, 119, 243));
	}
	ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

	m_label->setPosition(x + getWidth() / 2 - m_label->getWidth() / 2, y + m_label->getHeight() + 5);
	m_label->draw();
}

void menuBarButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}
