#pragma once
#include "ofMain.h"

class cursor
{
public:

	static ofImage cursorIcon;
	static bool isDefault;
	static bool isCamera;
	static bool isDragged;
	static int offsetX;
	static int offsetY;

	static void draw();

	//dynamic cursors
	static void setDefaultCursor();
	static void setHandCursor();
	static void setHandGrabCursor();
	static void setDragCursor();
	static void setRotateCursor();
	static void setScaleUpCursor();
	static void setScaleDownCursor();
	static void setZoomInCursor();
	static void setZoomOutCursor();
	static void setTargetCursor();
	static void setResetCursor();

	static void setDragged(bool drag);

	static bool isDefaultCursor();
	static bool isCameraCursor();
	static bool isDraggedCursor();


};

