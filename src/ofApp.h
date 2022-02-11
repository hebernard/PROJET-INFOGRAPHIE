#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "scene.h"
#include "camera.h"
#include "UI/menuBar.h"
#include "mainTheme.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

private:
	~ofApp();
	mainTheme& t = t.getInstance();
	menuBar* menu;
	scene& s = s.getInstance();

	camera* cam;

	void mousePressed(int x, int y, int button);
};
