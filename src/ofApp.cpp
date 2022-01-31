#include "ofApp.h"

void ofApp::setup()
{
	d = new dock();
}

void ofApp::update()
{
	d->update();
}

void ofApp::draw()
{
	s.drawObjects();

	// Always draw the ui last
	d->draw();
}

void ofApp::mousePressed(int x, int y, int button)
{
	cout << "Mouse pressed: " << x << ", " << y << endl;
}
