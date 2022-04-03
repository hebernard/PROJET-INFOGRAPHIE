#include "propertiesPanel.h"
#include "ofRectangle.h"
#include "UI/label.h"
#include "components/object.h"
#include "UI/hierarchy/hierarchySmallButton.h"
#include "scene.h"
#include "panel.h"
#include "cursor.h"
#include "utils.h"

propertiesPanel::propertiesPanel() : 
	backButton(new hierarchySmallButton("images/icons/back.png")),
	animateButton(new hierarchySmallButton("images/icons/animation.png")),
	materialButton(new hierarchySmallButton("images/icons/material.png")),
	position(centeredSlider("Position")),
	rotation(centeredSlider("Rotation")),
	scale(centeredSlider("Scale", true))
{
	ofRegisterMouseEvents(this);
	rect.width = 300;
	propertyWidth = rect.width - offsetX * 2;

	backButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		m_obj = nullptr;
		animationPanelVisible = false;
		scene& s = s.getInstance();
		s.currentSelected->propertiesOpened = false;

		animPanel.save();
	});

	animateButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		animationPanelVisible = !animationPanelVisible;
	});

	materialButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		matPanel.setObject(*m_obj);

		animationPanelVisible = false;
		materialPanelVisible = true;
	});

	position.resetButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->setPosition(glm::vec3(0, 0, 0));
		resetFocus();

		if (onUpdate != 0)
		{
			onUpdate();
		}
	});

	rotation.resetButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->setOrientation(glm::vec3(0, 0, 0));
		resetFocus();

		if (onUpdate != 0)
		{
			onUpdate();
		}
	});

	scale.resetButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.currentSelected->setScale(glm::vec3(1, 1, 1));
		resetFocus();

		if (onUpdate != 0)
		{
			onUpdate();
		}
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

	matPanel.backButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		materialPanelVisible = false;
	});

	position.onUpdate = [&](auto axis, float value)
	{
		m_obj->setPosition(m_obj->getPosition() + axis * value * ofGetLastFrameTime() * translationSpeed);

		if (onUpdate != 0)
		{
			onUpdate();
		}
	};

	rotation.onUpdate = [&](auto axis, float value)
	{
		m_obj->rotateDeg(value * ofGetLastFrameTime() * rotationSpeed, axis);

		if (onUpdate != 0)
		{
			onUpdate();
		}
	};

	scale.onUpdate = [&](auto axis, float value)
	{
		auto scaleAxis = scale.getLocked() ? glm::vec3(1, 1, 1) : axis;
		m_obj->setScale(m_obj->getScale() + scaleAxis * value * ofGetLastFrameTime() * scaleSpeed);

		if (onUpdate != 0)
		{
			onUpdate();
		}
	};
}

propertiesPanel::~propertiesPanel()
{
	delete backButton;
	delete animateButton;
	delete materialButton;
}

void propertiesPanel::draw(object& obj)
{
	if (m_obj == nullptr)
	{
		animPanel.setObject(obj);
		animPanel.load();
		m_obj = &obj;
	}

	if (rect.inside(ofGetMouseX(), ofGetMouseY()))
	{
		utils::isMouseOverUI = true;
	}

	position.update();
	rotation.update();
	scale.update();

	if (anchoredRight)
	{
		rect.height = ofGetHeight() - 125;
		rect.x = ofGetWidth() - rect.width - 20;
		rect.y = 100;
	}

	if (materialPanelVisible)
	{
		matPanel.draw();
		// Dont draw the normal panel
		return;
	}

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, obj.getName(), 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	if (obj.canBeAnimated)
	{
		animateButton->update(rect.x + rect.width - animateButton->getWidth() - 15, rect.y + 10);
		animateButton->draw();
	}

	if (obj.canHaveMaterial)
	{
		materialButton->update(animateButton->getX() - materialButton->getWidth() - 15, rect.y + 10);
		materialButton->draw();
	}

	drawLine(rect.x, rect.y + 55, rect.width);

	drawTransformSliders(obj);

	drawLine(rect.x + 30, rect.y + 310, rect.width - 60);

	int slidersMul = 3;
	if (!enableScaling)
	{
		slidersMul--;
	}
	if (!enableRotation)
	{
		slidersMul--;
	}

	int y = rect.y + (slidersMul * position.getHeight()) + 90;
	obj.drawProperties(rect.x + offsetX, y, propertyWidth);

	if (animationPanelVisible)
	{
		animPanel.draw(rect.x - 10);
	}
}

void propertiesPanel::mouseDragged(ofMouseEventArgs& args)
{
	animPanel.mouseDragged(args);
}

void propertiesPanel::mouseReleased(ofMouseEventArgs& args)
{
	if (position.dragStarted || rotation.dragStarted || scale.dragStarted)
	{
		// Refocus on the object once we're done dragging
		resetFocus();

		animPanel.addKeyFrame(*m_obj);
	}
}

void propertiesPanel::drawTransformSliders(object& obj)
{
	int y = rect.y + 75;

	position.draw(rect.x + offsetX, y, propertyWidth, obj.getPosition());
	y += position.getHeight();

	if (enableRotation)
	{
		rotation.draw(rect.x + offsetX, y, propertyWidth, obj.getOrientationEuler());
		y += rotation.getHeight();
	}

	if (enableScaling)
	{
		scale.draw(rect.x + offsetX, y, propertyWidth, obj.getScale());
	}
}

void propertiesPanel::drawLine(int x, int y, int width)
{
	ofPushStyle();
	ofSetColor(mainTheme::panelBorderColor());
	ofSetLineWidth(2);
	ofDrawLine(x, y, x + width, y);
	ofPopStyle();
}

void propertiesPanel::resetFocus()
{
	scene& s = s.getInstance();
	s.focusObject(*s.currentSelected);
}

void propertiesPanel::mouseMoved(ofMouseEventArgs& args) {}
void propertiesPanel::mousePressed(ofMouseEventArgs& args) {}
void propertiesPanel::mouseScrolled(ofMouseEventArgs& args)
{
	animPanel.mouseScrolled(args);
}
void propertiesPanel::mouseEntered(ofMouseEventArgs& args) {}
void propertiesPanel::mouseExited(ofMouseEventArgs& args) {}

void propertiesPanel::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void propertiesPanel::setHeight(int h)
{
	rect.height = h;
}
