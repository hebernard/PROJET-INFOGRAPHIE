#pragma once
#include "ofMain.h"

class cursor
{
public:

	static ofImage cursorIcon;

	static void setup();
	static void draw();

	//dynamic cursors
	static void setBasicCursor();
	static void setHandCursor();
	static void setDragCursor();
	static void setRotateCursor();
	static void setLeftCursor();
	static void setRightCursor();
	static void setLeftRotationCursor();
	static void setRightRotationCursor();
	static void setScaleUpCursor();
	static void setScaleDownCursor();
	static void setTargetCursor();

};

