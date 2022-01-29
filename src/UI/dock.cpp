#include "dock.h"
#include "dockButton.h"
#include "importPanel.h"

dock::dock() : ofxDatGuiComponent("dock"), mRect(), openedRect(), roundness(10), isOpened(false), dockButtons(), currentToggled(-1), m_importPanel(new importPanel())
{
	dockButton* btn = new dockButton(0, "images/icons/airplane.png", *this);
	dockButtons.push_back(btn);

	dockButton* btn2 = new dockButton(1, "images/icons/airplane.png", *this);
	dockButtons.push_back(btn2);

	dockButton* btn3 = new dockButton(2, "images/icons/airplane.png", *this);
	dockButtons.push_back(btn3);

	setTheme(new dockTheme());
}

dock::~dock()
{
	for (auto i : dockButtons)
	{
		delete i;
	}
}

void dock::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	mRect.width = theme->layout.width;
	mRect.height = theme->layout.height;

	openedRect.width = theme->layout.width * 4;
	openedRect.height = theme->layout.height;
}

void dock::update()
{
	setPosition(20, ofGetHeight() / 2 - mRect.height / 2);

	for (auto i : dockButtons)
	{
		i->update();
	}

	if (currentToggled == 0)
	{
		m_importPanel->update();
	}
}

void dock::drawClosed()
{
	ofPushStyle();
	ofFill();
	// dark border
	ofSetColor(ofColor(223, 223, 223));
	ofDrawRectRounded(mRect.x - 4, mRect.y - 4, mRect.width + 8, mRect.height + 8, roundness);

	// light border
	ofSetColor(ofColor::white);
	ofDrawRectRounded(mRect.x - 2, mRect.y - 2, mRect.width + 4, mRect.height + 4, roundness);

	ofSetColor(ofColor(245, 245, 245));
	ofDrawRectRounded(mRect.x, mRect.y, mRect.width, mRect.height, roundness);

	for (auto i : dockButtons)
	{
		i->draw();
	}
	ofPopStyle();
}

void dock::drawOpened()
{
	ofPushStyle();
	ofFill();
	// dark border
	ofSetColor(ofColor(223, 223, 223));
	ofDrawRectRounded(mRect.x - 4, mRect.y - 4, 0, mRect.width + openedRect.width + 8, mRect.height + 8, roundness);

	// light border
	ofSetColor(ofColor::white);
	ofDrawRectRounded(mRect.x - 2, mRect.y - 2, 0, mRect.width + openedRect.width + 4, mRect.height + 4, roundness);

	ofSetColor(ofColor(245, 245, 245));
	ofDrawRectRounded(mRect, roundness, 0, 0, roundness);

	// Opened window
	ofSetColor(ofColor::white);
	ofDrawRectRounded(openedRect, 0, roundness, roundness, 0);

	// Separator
	ofSetColor(ofColor(227, 227, 227));
	ofDrawLine(mRect.x + mRect.width, mRect.y, mRect.x + mRect.width, mRect.y + mRect.height);

	for (auto i : dockButtons)
	{
		i->draw();
	}

	if (currentToggled == 0)
	{
		m_importPanel->draw(openedRect.x, openedRect.y);
	}

	ofPopStyle();
}

void dock::draw()
{
	if (isOpened)
	{
		drawOpened();
	}
	else
	{
		drawClosed();
	}
}

void dock::setPosition(int x, int y)
{
	mRect.x = x;
	mRect.y = y;
	openedRect.x = x + mRect.width;
	openedRect.y = y;

	int offsetY = 14;
	int offsetX = 10;
	int spacing = 5;
	int buttonHeight = dockButtons.front()->getHeight();
	for (int i = 0; i < dockButtons.size(); i++)
	{
		dockButtons[i]->setPosition(x + offsetX, y + offsetY + (spacing * i) + (i * buttonHeight));
	}
}

void dock::notifyButtonToggled(int index, bool toggled)
{
	if (currentToggled != -1 && currentToggled != index)
	{
		dockButtons[currentToggled]->setChecked(false);
	}

	if (toggled)
	{
		currentToggled = index;
	}

	isOpened = toggled;
}