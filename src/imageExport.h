#pragma once

#include "ofMain.h"

class imageExport
{
public:
	
	void exportImages();
	void exportSeqImages();
	void updateTimer();

	bool isRunning = false;

	float timer = 0;
	int index = 0;
	ofFileDialogResult openFileResult;
};

