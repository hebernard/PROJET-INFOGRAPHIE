#include "cursor.h"

ofImage cursor::cursorIcon;
bool cursor::isDefault = true;
int cursor::offsetX = 10;
int cursor::offsetY = 10;

void cursor::draw()
{
	if (!isDefault && cursorIcon.isAllocated()) {
		cursorIcon.draw(ofGetMouseX() - offsetX, ofGetMouseY() - offsetY);
	}
}

void cursor::setDefaultCursor()
{
	isDefault = true;
	ofShowCursor();
}

void cursor::setHandCursor()
{
	isDefault = false;
	offsetX = 11;
	offsetY = 1;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/handCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setDragCursor()
{
	isDefault = false;
	offsetX = 15;
	offsetY = 15;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/dragCursor.png");
	cursorIcon.resize(30, 30);
}

void cursor::setRotateCursor()
{
	isDefault = false;
	offsetX = 15;
	offsetY = 15;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/rotateCursor.png");
	cursorIcon.resize(30, 30);
}

void cursor::setScaleUpCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/scaleUpCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setScaleDownCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/scaleDownCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setZoomInCursor()
{
	isDefault = false;
	offsetX = 15;
	offsetY = 15;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/zoomInCursor.png");
	cursorIcon.resize(30, 30);
}

void cursor::setZoomOutCursor()
{
	isDefault = false;
	offsetX = 15;
	offsetY = 15;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/zoomOutCursor.png");
	cursorIcon.resize(30, 30);
}

void cursor::setTargetCursor()
{
	isDefault = false;
	offsetX = 12;
	offsetY = 12;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/targetCursor.png");
	cursorIcon.resize(25, 25);
}

void cursor::setResetCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/resetCursor.png");
	cursorIcon.resize(20, 20);
}

bool cursor::isDefaultCursor()
{
	return isDefault;
}
