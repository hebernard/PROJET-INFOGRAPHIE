#include "hierarchyPanel.h"
#include "UI/label.h"

hierarchyPanel::hierarchyPanel() : m_label(new label("Hierarchy", "fonts/inter_regular.ttf", 14, ofColor::white))
{
	rect.width = 250;
	rect.y = 100;
}

void hierarchyPanel::draw(const vector<ofNode*>& objects)
{
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width;

	ofPushStyle();
	ofFill();

	ofSetColor(53);
	ofDrawRectRounded(rect.x - 2, rect.y - 2, 0, rect.width + 4, rect.height + 4, 8, 0, 0, 8);

	ofSetColor(49);
	ofDrawRectRounded(rect, 6, 0, 0, 6);

	m_label->setPosition(rect.x + 20, rect.y + 30);
	m_label->draw();

	ofPopStyle();
}
