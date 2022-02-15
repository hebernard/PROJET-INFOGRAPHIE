#include "propertiesPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "UI/hierarchy/hierarchySmallButton.h"
#include "scene.h"

propertiesPanel::propertiesPanel() : backButton(new hierarchySmallButton("images/icons/back.png"))
{
	rect.width = 300;
	rect.y = 100;

	backButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->propertiesOpened = false;
	});
}

void propertiesPanel::draw(const object& obj)
{
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width - 20;

	ofPushStyle();
	ofFill();

	ofSetColor(mainTheme::panelBorderColor());
	ofDrawRectRounded(rect.x - 2, rect.y - 2, rect.width + 4, rect.height + 4, 8);

	ofSetColor(mainTheme::panelColor());
	ofDrawRectRounded(rect, 6);

	drawText(rect.x + 60, rect.y + 32, obj.getName(), 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	ofSetColor(mainTheme::panelBorderColor());
	ofSetLineWidth(2);
	ofDrawLine(rect.x, rect.y + 55, rect.x + rect.width, rect.y + 55);

	// todo draw all the relevant properties of the object here

	ofPopStyle();
}
