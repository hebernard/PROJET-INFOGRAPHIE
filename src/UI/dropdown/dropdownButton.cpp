#include "dropdownButton.h"
#include "UI/label.h"

dropdownButton::dropdownButton(std::string iconPath, std::string text) : ofxDatGuiButton("dropdownButton"), m_label(new label(text, "fonts/inter_regular.ttf", 11, ofColor(t.ofFontColor))), icon()
{
	icon.load(iconPath);
	icon.resize(20, 20);
	setTheme(new dropdownButtonTheme());
}

void dropdownButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void dropdownButton::draw()
{
	ofPushStyle();
	ofFill();

	if (mMouseOver)
	{
		ofSetColor(t.toolBarButtonHoverColor);
		ofDrawRectangle(x - 2, y, getWidth() + 4, getHeight());
	}

	if (icon.isAllocated())
	{
		ofSetColor(t.ofFontColor);
		icon.draw(x + 20, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	m_label->draw();
	ofPopStyle();
}

void dropdownButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
	m_label->setPosition(x + icon.getWidth() + 20 * 2, y + getHeight() / 2 + m_label->getHeight() / 2);
}
