#include "hierarchyPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"

hierarchyPanel::hierarchyPanel() : m_label(new label("Hierarchy", "fonts/inter_regular.ttf", 14, ofColor::white)), icon()
{
	rect.width = 300;
	rect.y = 100;

	icon.load("images/icons/hierarchy.png");
	icon.resize(24, 24);
}

void hierarchyPanel::draw(const vector<object*>& objects)
{
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width;

	ofPushStyle();
	ofFill();

	ofSetColor(53);
	ofDrawRectRounded(rect.x - 2, rect.y - 2, 0, rect.width + 4, rect.height + 4, 8, 0, 0, 8);

	ofSetColor(45);
	ofDrawRectRounded(rect, 6, 0, 0, 6);

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(rect.x + 15, rect.y + icon.getHeight() / 2);
	}
	m_label->setPosition(rect.x + 60, rect.y + 32);
	m_label->draw();

	ofSetColor(53);
	ofSetLineWidth(2);
	ofDrawLine(rect.x, rect.y + 55, rect.x + rect.width, rect.y + 55);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects.at(i)->drawHierarchy(rect.x, rect.y + 56 + (i * 40));
	}

	ofPopStyle();
}
