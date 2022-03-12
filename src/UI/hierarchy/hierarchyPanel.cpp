#include "hierarchyPanel.h"
#include "scene.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "mainTheme.h"
#include "panel.h"
#include "utils.h"
#include "cameraHierarchyButton.h"

hierarchyPanel::hierarchyPanel() : icon()
{
	setup();
}

hierarchyPanel::~hierarchyPanel()
{
	delete cameraButton;
}

void hierarchyPanel::setup()
{

	icon.load("images/icons/hierarchy.png");
	icon.resize(24, 24);

	rect.width = 300;
	rect.y = 100;
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width - 20;

	cameraButton = new cameraHierarchyButton("images/icons/camera.png", "Camera");
	cameraButton->propertiesButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		isDrawingCameraProp = true;
	});

	camProp.backButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		isDrawingCameraProp = false;
	});
	
}

void hierarchyPanel::draw(const vector<object*>& objects)
{
	if (rect.inside(ofGetMouseX(), ofGetMouseY()))
	{
		utils::isMouseOverUI = true;
	}

	if (isDrawingCameraProp)
	{
		camProp.draw();
	}
	else
	{
		rect.height = ofGetHeight() - 125;
		rect.x = ofGetWidth() - rect.width - 20;

		drawOpened(objects);
	}

}

void hierarchyPanel::drawOpened(const vector<object*>& objects)
{
	//draw panel
	drawPanel(rect);

	//draw icons
	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(rect.x + 15, rect.y + icon.getHeight() / 2);
	}

	//draw text
	drawText(rect.x + 60, rect.y + 32, "Hierarchy", 14);

	//draw seperator
	ofPushStyle();
	ofSetColor(mainTheme::panelBorderColor());
	ofSetLineWidth(2);
	ofDrawLine(rect.x, rect.y + 55, rect.x + rect.width, rect.y + 55);
	ofPopStyle();

	cameraButton->update(rect.x, rect.y + 56);
	cameraButton->draw();

	//draw hierarchy objects
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects.at(i)->drawHierarchy(rect.x, rect.y + 56 + ((i + 1) * 40));
	}
}

