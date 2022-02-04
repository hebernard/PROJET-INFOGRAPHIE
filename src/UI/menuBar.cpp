#include "menuBar.h"
#include "UI/dropdown/dropdown.h"
#include "dropdown/dropdownButton.h"

menuBar::menuBar() : ofxDatGuiComponent("menuBar"), rect(), logo(), dropdown2d(new dropdown(0, "2D", *this)), dropdown3d(new dropdown(1, "3D", *this))
{
	rect.width = ofGetWidth();
	rect.height = 70;

	logo.load("images/logo.png");
	logo.resize(22, 22);

	dropdown2d->addButton(new dropdownButton("images/icons/airplane.png", "Button 1"));
	dropdown2d->addButton(new dropdownButton("images/icons/airplane.png", "Button 2"));
}

void menuBar::draw()
{
	ofPushStyle();
	ofFill();
	ofSetColor(18);
	ofDrawRectangle(rect);

	drawLogo();
	drawLine();

	dropdown2d->draw();
	dropdown3d->draw();

	ofPopStyle();
}

void menuBar::update()
{
	rect.width = ofGetWidth();

	int posX = 180;
	int posY = rect.height / 2 - dropdown2d->getHeight() / 2;
	dropdown2d->setPosition(posX, posY);
	dropdown2d->update();

	posX += dropdown2d->getWidth() + 5;
	dropdown3d->setPosition(posX, posY);
	dropdown3d->update();

	posX += dropdown3d->getWidth() + 5;

}

void menuBar::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void menuBar::notifyDropdownClicked(int index)
{
	// This is ugly but works for now
	if (index == 0)
	{
		dropdown3d->setChecked(false);
	}
	else if (index == 1)
	{
		dropdown2d->setChecked(false);
	}
}

void menuBar::drawLogo()
{
	ofSetColor(36);
	ofDrawRectRounded(20, rect.height / 2 - 15, 34, 34, 6);

	ofSetColor(70);
	ofDrawRectRounded(20, rect.height / 2 - 17, 34, 34, 6);

	ofSetColor(ofColor::white);
	logo.draw(26, rect.height / 2 - 9);
}

void menuBar::drawLine()
{
	ofSetLineWidth(2);
	ofSetColor(53);
	ofDrawLine(0, 71, ofGetWidth(), 71);
}
