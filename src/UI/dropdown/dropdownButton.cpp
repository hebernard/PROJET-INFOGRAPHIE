#include "dropdownButton.h"
#include "UI/label.h"
#include "mainTheme.h"
#include "cursor.h"

dropdownButton::dropdownButton(std::string iconPath, std::string text) : ofxDatGuiButton("dropdownButton"), m_text(text), icon()
{
	icon.load(iconPath);
	icon.resize(20, 20);
	setTheme(new dropdownButtonTheme());

	textSize = label::getSize(text, 11, mainTheme::fontRegularPath);
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
		cursor::setHandCursor();
		ofSetColor(mainTheme::panelButtonHoverColor());
		ofDrawRectangle(x - 2, y, getWidth() + 4, getHeight());
	}

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(x + 20, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	drawText(
		x + icon.getWidth() + 20 * 2,
		y + getHeight() / 2 + textSize.y / 2,
		m_text, 
		11, 
		mainTheme::fontColor(),
		mainTheme::fontRegularPath
	);
	ofPopStyle();
}

void dropdownButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
}
