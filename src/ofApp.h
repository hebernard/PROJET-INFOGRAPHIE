#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "scene.h"
#include "camera.h"
#include "ui/menuBar/menuBar.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mouseReleased(int x, int y, int button);

private:
	~ofApp();
	menuBar* menu;

	scene& s = s.getInstance();

	void mousePressed(int x, int y, int button);
};
