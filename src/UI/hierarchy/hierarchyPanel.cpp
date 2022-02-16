#include "hierarchyPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "mainTheme.h"
#include "panel.h"


hierarchyPanel::hierarchyPanel() : minimized(false), icon(), iconMinimize()
{
	//ofxDatGuiButton::onButtonEvent(iconMinimize, &hierarchyPanel::onMinimized);
		//(iconMinimize, &hierarchyPanel::onMinimized);

	if (minimized) {
		icon.load("images/icons/hierarchy.png");
		icon.resize(18, 18);
		iconMinimize.load("images/icons/down.png");
		iconMinimize.resize(12, 12);
	}
	else {
		icon.load("images/icons/hierarchy.png");
		icon.resize(24, 24);
		iconMinimize.load("images/icons/up.png");
		iconMinimize.resize(18, 18);
	}

	rect.width = 300;
	rect.y = 100;
}

void hierarchyPanel::draw(const vector<object*>& objects)
{
	if (minimized) {
		drawMinimized();
	}
	else {
		drawFull(objects);
	}
}

void hierarchyPanel::drawFull(const vector<object*>& objects)
{
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(rect.x + 15, rect.y + icon.getHeight() / 2);
		iconMinimize.draw(rect.x + 245, rect.y + iconMinimize.getHeight() / 2 + 8);
	}

	drawText(rect.x + 60, rect.y + 32, "Hierarchy", 14);

	ofPushStyle();
	ofSetColor(mainTheme::panelBorderColor());
	ofSetLineWidth(2);
	ofDrawLine(rect.x, rect.y + 55, rect.x + rect.width, rect.y + 55);
	ofPopStyle();

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects.at(i)->drawHierarchy(rect.x, rect.y + 56 + (i * 40));
	}
}

void hierarchyPanel::drawMinimized()
{
	rect.height = 40;
	rect.width = 200;
	rect.x = ofGetWidth() - rect.width - 60;
	rect.y = 80;

	drawPanel(rect);

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(rect.x + 15, rect.y + icon.getHeight() / 2);
		iconMinimize.draw(rect.x + 165, rect.y + iconMinimize.getHeight() / 2 + 8);
	}

	drawText(rect.x + 60, rect.y + 24, "Hierarchy", 9);
}

void hierarchyPanel::setMinimized()
{
	minimized = !minimized;

	if (minimized) {
		icon.load("images/icons/hierarchy.png");
		icon.resize(12, 12);
		iconMinimize.load("images/icons/down.png");
		iconMinimize.resize(9, 9);
	}
	else {
		icon.load("images/icons/hierarchy.png");
		icon.resize(24, 24);
		iconMinimize.load("images/icons/up.png");
		iconMinimize.resize(18, 18);
	}
}

bool hierarchyPanel::getMinimized()
{
	return minimized;
}
