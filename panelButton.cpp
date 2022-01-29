#include "panelButton.h"
#include "label.h"

panelButton::panelButton(string iconPath) : ofxDatGuiButton("panelButton"), m_label(new label("Import", "fonts/segoe_normal.ttf", 12, ofColor(63,63,63))), iconOffset(14)
{
	icon.load(iconPath);
	icon.resize(16, 16);
	setTheme(new panelButtonTheme());
}

void panelButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void panelButton::draw()
{
	ofPushStyle();
	ofFill();
	if (mFocused && mMouseDown)
	{
		ofSetColor(ofColor(227, 227, 227));
	}
	else if (mMouseOver)
	{
		ofSetColor(ofColor(238, 238, 238));
	}
	else
	{
		ofSetColor(ofColor(245, 245, 245));
	}

	ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

	if (icon.isAllocated())
	{
		icon.draw(x + iconOffset, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	m_label->draw();
	ofPopStyle();
}

void panelButton::update()
{
	ofxDatGuiComponent::update();
}

void panelButton::setPosition(int newX, int newY)
{
	x = newX;
	y = newY;
	m_label->setPosition(x + icon.getWidth() + iconOffset * 2, y + getHeight() - m_label->getHeight());
}
