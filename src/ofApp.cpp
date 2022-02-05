#include "ofApp.h"

void ofApp::setup()
{
	ofSetBackgroundColor(36);
	ofSetWindowTitle("IFT-3100 - Projet de session");

	menu = new menuBar();

	cam.setAutoDistance(false);
	cam.setPosition(0, 1, 5);
	cam.setTarget(glm::vec3(0, 1, 0));
	cam.setNearClip(0.1f);
}

void ofApp::update()
{
	cam.setControlArea(ofRectangle(0, 70, ofGetWidth(), ofGetHeight()));
	menu->update();
}

void ofApp::draw()
{
	cam.begin();
	ofEnableDepthTest();

	s.drawGrid();

	ofNoFill();
	ofDrawSphere(glm::vec3(0, 1, 0), 1);
	ofDrawCircle(0, 1, 1.2f);
	s.drawObjects();

	ofDisableDepthTest();
	cam.end();

	menu->draw();
}

void ofApp::mousePressed(int x, int y, int button)
{
	cout << "Mouse pressed: " << x << ", " << y << endl;
}
