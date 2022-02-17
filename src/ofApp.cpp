#include "ofApp.h"
#include "mainTheme.h"
#include "cursor.h"

void ofApp::setup()
{
	//setup darkTheme by default
	mainTheme::darkTheme = true;

	ofSetBackgroundColor(mainTheme::sceneBackgroundColor());
	ofSetWindowTitle("IFT-3100 - Projet de session");

	//setup cursor 
	cursor::setup();

	//setup menu UI
	menu = new menuBar();

	//setup camera
	cam = new camera();

	cam->setAutoDistance(false);
	cam->setPosition(0, 1, 5);
	cam->setTarget(glm::vec3(0, 1, 0));
	cam->setNearClip(0.1f);
	s.camera = cam;

	// setup dummyObjects by default
	s.setupObjects();

}

void ofApp::update()
{
	cam->setControlArea(ofRectangle(0, 70, ofGetWidth(), ofGetHeight()));

	//update menuUI
	menu->update();
}

void ofApp::draw()
{

	cam->begin();//-----------------------begin of cam------------------------------//
	ofEnableDepthTest();

	//draw grid
	s.drawGrid();

	//draw objects
	s.drawObjects();

	ofDisableDepthTest();
	cam->end();//-----------------------end of cam------------------------------//

	// UI must be drawn at the end & objects are added to the hierarchy
	menu->draw();
	s.drawHierarchyUI();
	cursor::draw();
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
