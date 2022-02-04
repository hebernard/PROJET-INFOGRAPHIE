#include "ofApp.h"

void ofApp::setup()
{
	ofSetBackgroundColor(ofColor(36, 36, 36));
	ofSetWindowTitle("IFT-3100 - Projet de session");

	menu = new menuBar();

	cam.setAutoDistance(false);
	cam.setDistance(200);
}

void ofApp::update()
{
	cam.setControlArea(ofRectangle(0, 70, ofGetWidth(), ofGetHeight()));

	menu->update();
}

void ofApp::draw()
{
	cam.begin();
	ofNoFill();
	ofDrawSphere(64);
	ofDrawCircle(0, 0, 72);
	cam.end();

	s.drawObjects();

	menu->draw();
}

void ofApp::mousePressed(int x, int y, int button)
{
	cout << "Mouse pressed: " << x << ", " << y << endl;
}
