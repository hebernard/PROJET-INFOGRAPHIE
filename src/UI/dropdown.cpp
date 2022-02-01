#include "dropdown.h"
#include "label.h"

dropdown::dropdown(std::string text) : ofxDatGuiButton("dropdown"), mLabel(new label(text, "fonts/roboto_regular.ttf", 13, ofColor(255, 255, 255, 128))), downArrow()
{
	downArrow.load("images/icons/down_arrow.png");
	downArrow.resize(20, 20);
	setTheme(new dropdownTheme());
}

void dropdown::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	int width = mLabel->getWidth() + 50;
	ofxDatGuiComponent::setWidth(width, theme->layout.labelWidth);
}

void dropdown::draw()
{
	ofPushStyle();
	ofFill();

	if (mMouseOver)
	{
		ofSetColor(ofColor(35, 35, 35));
		ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

		if (downArrow.isAllocated())
		{
			ofSetColor(ofColor::white);
			downArrow.draw(mLabel->getX() + mLabel->getWidth() + 5, y + getHeight() / 2 - 10);
		}

		mLabel->setColor(ofColor::white);
		mLabel->draw();
	}
	else 
	{
		mLabel->setColor(ofColor(255, 255, 255, 128));
		mLabel->draw();
	}
	/*if (mFocused && mMouseDown)
	{
		ofSetColor(ofColor(227, 227, 227));
		ofDrawRectRounded(x, y, getWidth(), getHeight(), 8);
	}
	else if (mMouseOver)
	{
		ofSetColor(ofColor(238, 238, 238));
	}*/

	ofPopStyle();
}

void dropdown::update()
{
	ofxDatGuiComponent::update();
}

void dropdown::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	mLabel->setPosition(x + 15, y + mLabel->getHeight() + 14);
}
