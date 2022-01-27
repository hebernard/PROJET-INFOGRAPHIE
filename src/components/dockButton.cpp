#include "dockButton.h"
#include "dock.h"

dockButton::dockButton(int index, string iconPath, dock& dock) : ofxDatGuiToggle("dockButton"), m_dock(dock), icon(), roundness(6), index(index)
{
	mType = ofxDatGuiType::BUTTON;

	icon.load(iconPath);
	icon.resize(20, 20);
	setTheme(new dockButtonTheme());

	onToggleEvent(this, &dockButton::onToggled);
}

bool dockButton::operator!=(const dockButton& other)
{
	return x != other.x || y != other.y;
}

void dockButton::onToggled(ofxDatGuiToggleEvent e)
{
	m_dock.notifyButtonToggled(index, getChecked());
}

void dockButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void dockButton::draw()
{
	ofPushStyle();
	ofFill();
	if ((mFocused && mMouseDown) || getChecked())
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

	ofDrawRectRounded(x, y, getWidth(), getHeight(), roundness);

	if (icon.isAllocated())
	{
		icon.draw(x + (getWidth() / 2 - icon.getWidth() / 2), y + (getHeight() / 2 - icon.getHeight() / 2));
	}
	ofPopStyle();
}

void dockButton::update()
{
	ofxDatGuiComponent::update();
}

void dockButton::setPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}

int dockButton::getHeight()
{
	return mStyle.height;
}