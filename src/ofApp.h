#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "./UI/dock.h"
#include "scene.h"
#include "camera.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

private:
	dock* d;
	scene& s = s.getInstance();

	camera cam;

	void mousePressed(int x, int y, int button);
};
