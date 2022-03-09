#include "ofApp.h"
#include "mainTheme.h"
#include "cursor.h"
#include "utils.h"

void ofApp::setup()
{
	ofEnableAlphaBlending();
	ofSetCircleResolution(50);
	ofSetFrameRate(60);

	//setup darkTheme by default
	mainTheme::darkTheme = true;

	ofSetBackgroundColor(mainTheme::sceneBackgroundColor());
	ofSetWindowTitle("IFT-3100 - Projet de session");

	//setup menu UI
	menu = new menuBar();

	// Add the main camera to the scene
	s.addCamera();

	// setup dummyObjects by default
	s.setupObjects();

}

void ofApp::update()
{
	menu->update();
}

void ofApp::draw()
{
	if (!cursor::isCameraCursor() && !cursor::isDraggedCursor()) { cursor::setDefaultCursor(); }

	ofEnableDepthTest();
	auto cameras = s.getCameras();
	for (int i = 0; i < cameras.size(); i++)
	{
		cameras.at(i)->render(s, i);
	}

	ofDisableDepthTest();

	// UI must be drawn at the end & objects are added to the hierarchy
	menu->draw();
	s.drawHierarchyUI();
	cursor::draw();

	// Give time for the components to check the mouse state before setting back to false
	utils::mouseReleased = false;
	utils::mousePressed = false;

	if (utils::isMouseOverUI)
	{
		s.disableMouseInputs();
	}
	else
	{
		s.enableMouseInputs();
	}
	utils::isMouseOverUI = false;
}

ofApp::~ofApp()
{
	delete menu;
}

void ofApp::mousePressed(int x, int y, int button)
{
	cout << "Mouse pressed: " << x << ", " << y << endl;
	if (button == 0)
	{
		utils::mousePressed = true;
	}
}

void ofApp::mouseReleased(int x, int y, int button)
{
	if (button == 0)
	{
		utils::mouseReleased = true;
	}
}
