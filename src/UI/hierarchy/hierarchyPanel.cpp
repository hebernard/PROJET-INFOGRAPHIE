#include "hierarchyPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"

hierarchyPanel::hierarchyPanel() : m_label(new label("Hierarchy", "fonts/inter_regular.ttf", 14, ofColor::white))
{
	rect.width = 300;
	rect.y = 100;
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

	m_label->setPosition(rect.x + 20, rect.y + 35);
	m_label->draw();

	ofSetColor(53);
	ofSetLineWidth(2);
	ofDrawLine(rect.x, rect.y + 55, rect.x + rect.width, rect.y + 55);

	if (objects.size() > 0)
	{
		objects.front()->drawHierarchy(rect.x, rect.y + 100);
	}

	ofPopStyle();
}
