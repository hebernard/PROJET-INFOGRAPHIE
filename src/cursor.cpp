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
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/dragCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setRotateCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/rotateCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setLeftCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/leftCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setRightCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/rightCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setHorizontalTranslateCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/horizontalTranslateCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setLeftRotationCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/leftRotationCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setRightRotationCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/rightRotationCursor.png");
	cursorIcon.resize(20, 20);
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

void cursor::setTargetCursor()
{
	isDefault = false;
	offsetX = 10;
	offsetY = 10;
	ofHideCursor();
	cursorIcon.load("images/icons/cursor/targetCursor.png");
	cursorIcon.resize(20, 20);
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
