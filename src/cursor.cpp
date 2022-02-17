#include "cursor.h"

ofImage cursor::cursorIcon;

void cursor::setup()
{
	ofHideCursor();
	setBasicCursor();
}

void cursor::draw()
{
	cursorIcon.draw(ofGetMouseX(), ofGetMouseY());
}

void cursor::setBasicCursor()
{
	cursorIcon.load("images/icons/cursor/basicCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setHandCursor()
{
	cursorIcon.load("images/icons/cursor/handCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setDragCursor()
{
	cursorIcon.load("images/icons/cursor/dragCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setRotateCursor()
{
	cursorIcon.load("images/icons/cursor/rotateCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setLeftCursor()
{
	cursorIcon.load("images/icons/cursor/leftCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setRightCursor()
{
	cursorIcon.load("images/icons/cursor/rightCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setLeftRotationCursor()
{
	cursorIcon.load("images/icons/cursor/leftRotationCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setRightRotationCursor()
{
	cursorIcon.load("images/icons/cursor/rightRotationCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setScaleUpCursor()
{
	cursorIcon.load("images/icons/cursor/scaleUpCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setScaleDownCursor()
{
	cursorIcon.load("images/icons/cursor/scaleDownCursor.png");
	cursorIcon.resize(20, 20);
}

void cursor::setTargetCursor()
{
	cursorIcon.load("images/icons/cursor/targetCursor.png");
	cursorIcon.resize(20, 20);
}
