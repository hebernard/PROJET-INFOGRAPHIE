#include "hierarchyPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "mainTheme.h"
#include "panel.h"

hierarchyPanel::hierarchyPanel() : icon()
{
	rect.width = 300;
	rect.y = 100;

	icon.load("images/icons/hierarchy.png");
	icon.resize(24, 24);
}

void hierarchyPanel::draw(const vector<object*>& objects)
{
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(rect.x + 15, rect.y + icon.getHeight() / 2);
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
