#include "ofApp.h"
#include "mainTheme.h"

void ofApp::setup()
{
	//set DarkTheme by default
	mainTheme::darkTheme = true;

	ofSetBackgroundColor(mainTheme::sceneBackgroundColor());
	ofSetWindowTitle("IFT-3100 - Projet de session");

	menu = new menuBar();
	cam = new camera();

	cam->setAutoDistance(false);
	cam->setPosition(0, 1, 5);
	cam->setTarget(glm::vec3(0, 1, 0));
	cam->setNearClip(0.1f);
	s.camera = cam;

	// Add dummy objects
	s.setupObjects();

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
