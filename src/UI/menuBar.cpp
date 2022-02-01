#include "menuBar.h"
#include "dropdown.h"

menuBar::menuBar() : ofxDatGuiComponent("menuBar"), rect(), logo(), dropdown2d(new dropdown("2D")), dropdown3d(new dropdown("3D"))
{
	rect.width = ofGetWidth();
	rect.height = 70;

	logo.load("images/logo.png");
	logo.resize(22, 22);
}

void menuBar::draw()
{
	ofPushStyle();
	ofFill();
	ofSetColor(ofColor(18, 18, 18));
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

	dropdown2d->setPosition(200, rect.height / 2 - dropdown2d->getHeight() / 2);
	dropdown2d->update();

	dropdown3d->setPosition(200 + dropdown2d->getWidth() + 15, rect.height / 2 - dropdown3d->getHeight() / 2);
	dropdown3d->update();
}

void menuBar::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void menuBar::drawLogo()
{
	ofSetColor(ofColor(36, 36, 36));
	ofDrawRectRounded(20, rect.height / 2 - 15, 34, 34, 6);

	ofSetColor(ofColor(70, 70, 70));
	ofDrawRectRounded(20, rect.height / 2 - 17, 34, 34, 6);

	ofSetColor(ofColor::white);
	logo.draw(26, rect.height / 2 - 9);
}

void menuBar::drawLine()
{
	ofSetLineWidth(2);
	ofSetColor(ofColor(53, 53, 53));
	ofDrawLine(0, 71, ofGetWidth(), 71);
}
