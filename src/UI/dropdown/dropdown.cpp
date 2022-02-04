#include "dropdown.h"
#include "../label.h"
#include "../menuBar.h"
#include "dropdownButton.h"

dropdown::dropdown(int i, std::string text, menuBar& menu) : ofxDatGuiToggle("dropdown"), index(i), opened(false), mLabel(new label(text, "fonts/inter_regular.ttf", 13, ofColor(255, 255, 255, 128))), downArrow(), panel(), m_menu(menu)
{
	downArrow.load("images/icons/down_arrow.png");
	downArrow.resize(20, 20);
	setTheme(new dropdownTheme());

	onToggleEvent(this, &dropdown::onToggled);
}

void dropdown::onToggled(ofxDatGuiToggleEvent e)
{
	m_menu.notifyDropdownClicked(index);
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

	if (mMouseOver || getChecked())
	{
		ofSetColor(35);
		ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

		if (downArrow.isAllocated())
		{
			ofSetColor(ofColor::white);
			downArrow.draw(mLabel->getX() + mLabel->getWidth() + 5, y + getHeight() / 2 - 10);
		}

		mLabel->setColor(ofColor::white);
		mLabel->draw();

		if (getChecked())
		{
			panel.draw();
		}
	}
	else 
	{
		mLabel->setColor(ofColor(255, 255, 255, 128));
		mLabel->draw();
	}

	ofPopStyle();
}

void dropdown::update()
{
	ofxDatGuiComponent::update();
	if (getChecked())
	{
		panel.update(x - 25, y + 50);
		if (ofGetMouseX() < panel.rect.getX() || ofGetMouseX() > panel.rect.getX() + panel.rect.getWidth() ||
			ofGetMouseY() < y || ofGetMouseY() > panel.rect.getY() + panel.rect.getHeight())
		{
			m_menu.notifyDropdownClicked(-1);
		}
	}
}

void dropdown::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	mLabel->setPosition(x + 15, y + mLabel->getHeight() + 14);
}

void dropdown::addButton(dropdownButton* button)
{
	panel.addButton(button);
}
