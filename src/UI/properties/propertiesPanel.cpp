#include "propertiesPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "UI/hierarchy/hierarchySmallButton.h"
#include "scene.h"
#include "panel.h"

propertiesPanel::propertiesPanel() : 
	backButton(new hierarchySmallButton("images/icons/back.png")),
	position(centeredSlider("Position")),
	rotation(centeredSlider("Rotation")),
	scale(centeredSlider("Scale", true))
{
	ofRegisterMouseEvents(this);
	rect.width = 300;
	rect.y = 100;

	backButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->propertiesOpened = false;
	});

	position.resetButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->setPosition(glm::vec3(0, 0, 0));
		resetFocus();
	});

	rotation.resetButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->setOrientation(glm::vec3(0, 0, 0));
		resetFocus();
	});

	scale.resetButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->setScale(glm::vec3(1, 1, 1));
		resetFocus();
	});

	scale.lockedButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scale.setLocked(!scale.getLocked());
		if (scale.getLocked())
		{
			scene& s = s.getInstance();
			s.currentSelected->setScale(glm::vec3(1, 1, 1));
		}
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
	int offsetX = 15;
	int sliderWidth = rect.width - offsetX * 2;
	position.draw(rect.x + offsetX, rect.y + 75, sliderWidth, obj.getPosition());
	rotation.draw(rect.x + offsetX, rect.y + 155, sliderWidth, obj.getOrientationEuler());
	scale.draw(rect.x + offsetX, rect.y + 235, sliderWidth, obj.getScale());

	obj.setPosition(obj.getPosition() + position.axis * position.value * ofGetLastFrameTime() * translationSpeed);
	obj.rotateDeg(rotation.value * ofGetLastFrameTime() * rotationSpeed, rotation.axis);

	auto scaleAxis = scale.getLocked() ? glm::vec3(1, 1, 1) : scale.axis;
	obj.setScale(obj.getScale() + scaleAxis * scale.value * ofGetLastFrameTime() * scaleSpeed);
}

void propertiesPanel::mouseMoved(ofMouseEventArgs& args)
{
}

void propertiesPanel::mouseDragged(ofMouseEventArgs& args)
{
	if (!rotation.dragStarted && !scale.dragStarted)
	{
		position.mouseDragged(args);
	}

	if (!position.dragStarted && !scale.dragStarted)
	{
		rotation.mouseDragged(args);
	}

	if (!position.dragStarted && !rotation.dragStarted)
	{
		scale.mouseDragged(args);
	}
}

void propertiesPanel::mousePressed(ofMouseEventArgs& args)
{
}

void propertiesPanel::mouseReleased(ofMouseEventArgs& args)
{
	if (position.dragStarted || rotation.dragStarted || scale.dragStarted)
	{
		// Refocus on the object once we're done dragging
		resetFocus();
	}

	position.mouseReleased(args);
	rotation.mouseReleased(args);
	scale.mouseReleased(args);
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

void propertiesPanel::resetFocus()
{
	scene& s = s.getInstance();
	s.focusObject(*s.currentSelected);
}
