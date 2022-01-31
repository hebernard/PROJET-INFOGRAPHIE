#include "ofApp.h"

void ofApp::setup()
{
	d = new dock();
	cam.setAutoDistance(false);
	cam.setDistance(200);
}

void ofApp::update()
{
	d->update();
}

void ofApp::draw()
{
	cam.begin();
	ofNoFill();
	ofDrawSphere(64);
	ofDrawCircle(0, 0, 72);
	cam.end();

	s.drawObjects();

	// Always draw the ui last
	d->draw();
}

void ofApp::mousePressed(int x, int y, int button)
{
	cout << "Mouse pressed: " << x << ", " << y << endl;
}
