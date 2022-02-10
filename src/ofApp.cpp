#include "ofApp.h"
#include "components/sphere.h"

void ofApp::setup()
{
	ofSetBackgroundColor(36);
	ofSetWindowTitle("IFT-3100 - Projet de session");

	menu = new menuBar();
	cam = new camera();

	cam->setAutoDistance(false);
	cam->setPosition(0, 1, 5);
	cam->setTarget(glm::vec3(0, 1, 0));
	cam->setNearClip(0.1f);
	s.camera = cam;

	sphere* sp = new sphere(1);
	sp->setPosition(glm::vec3(0, 1, 0));
	s.addObject(sp);
}

void ofApp::update()
{
	cam->setControlArea(ofRectangle(0, 70, ofGetWidth(), ofGetHeight()));
	menu->update();
}

void ofApp::draw()
{
	cam->begin();
	ofEnableDepthTest();

	s.drawGrid();

	ofNoFill();
	ofDrawCircle(0, 1, 1.2f);
	s.drawObjects();

	ofDisableDepthTest();
	cam->end();

	// UI must be drawn at the end
	menu->draw();
	s.drawHierarchyUI();
}

ofApp::~ofApp()
{
	delete menu;
	delete cam;
}

void ofApp::mousePressed(int x, int y, int button)
{
	cout << "Mouse pressed: " << x << ", " << y << endl;
}
