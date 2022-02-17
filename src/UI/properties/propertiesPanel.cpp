#include "propertiesPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "UI/hierarchy/hierarchySmallButton.h"
#include "scene.h"
#include "panel.h"

propertiesPanel::propertiesPanel() : backButton(new hierarchySmallButton("images/icons/back.png")), position(centeredSlider("Position")), rotation(centeredSlider("Rotation"))
{
	ofRegisterMouseEvents(this);
	rect.width = 300;
	rect.y = 100;

	backButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->propertiesOpened = false;
	});
}

void propertiesPanel::draw(object& obj)
{
	rect.height = ofGetHeight() - 150;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, obj.getName(), 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	ofPushStyle();
	ofSetColor(mainTheme::panelBorderColor());
	ofSetLineWidth(2);
	ofDrawLine(rect.x, rect.y + 55, rect.x + rect.width, rect.y + 55);
	ofPopStyle();

	// todo draw all the relevant properties of the object here
	position.draw(rect.x + 30, rect.y + 85, obj.getPosition());
	rotation.draw(rect.x + 30, rect.y + 200, obj.getOrientationEuler());

	obj.setPosition(obj.getPosition() + position.axis * position.value * ofGetLastFrameTime());
	obj.rotateAroundDeg(rotation.value * ofGetLastFrameTime() * 5, rotation.axis, obj.getCenter());
	//obj.rotateAroundDeg(1, glm::vec3(1, 0, 0), obj.getCenter());
	//obj.rotateDeg(30, glm::vec3(1, 0, 0));
	//obj.tiltDeg(rotation.value * ofGetLastFrameTime() * 10);
}

void propertiesPanel::mouseMoved(ofMouseEventArgs& args)
{
}

void propertiesPanel::mouseDragged(ofMouseEventArgs& args)
{
	position.mouseDragged(args);
	rotation.mouseDragged(args);
}

void propertiesPanel::mousePressed(ofMouseEventArgs& args)
{
}

void propertiesPanel::mouseReleased(ofMouseEventArgs& args)
{
	position.mouseReleased(args);
	rotation.mouseReleased(args);

	// Refocus on the object once we're done dragging
	/*scene& s = s.getInstance();
	s.focusObject(*s.currentSelected);*/
}

void propertiesPanel::mouseScrolled(ofMouseEventArgs& args)
{
}

void propertiesPanel::mouseEntered(ofMouseEventArgs& args)
{
}

void propertiesPanel::mouseExited(ofMouseEventArgs& args)
{
}
