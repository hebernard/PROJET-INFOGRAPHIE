#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "./UI/dock.h"
#include "scene.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

private:
	dock* d;
	scene& s = s.getInstance();

	void mousePressed(int x, int y, int button);
};
