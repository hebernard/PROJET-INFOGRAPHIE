#include "propertiesPanel.h"
#include "ofRectangle.h"
#include "ui/label.h"
#include "objects/object.h"
#include "ui/hierarchy/hierarchySmallButton.h"
#include "scene.h"
#include "ui/panel.h"
#include "utils/cursor.h"
#include "utils/utils.h"

propertiesPanel::propertiesPanel() :
	backButton(new hierarchySmallButton("images/icons/back.png")),
	animateButton(new hierarchySmallButton("images/icons/animation.png")),
	materialButton(new hierarchySmallButton("images/icons/material.png")),
	position(centeredSlider("Position")),
	rotation(centeredSlider("Rotation")),
	scale(centeredSlider("Scale", true)),
	transformGroup("Transform")
{
	ofRegisterMouseEvents(this);
	rect.width = 300;
	propertyWidth = rect.width - offsetX * 2;
	transformGroup.setWidth(propertyWidth);

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

	if (anchoredRight)
	{
		rect.height = ofGetHeight() - 125;
		rect.x = ofGetWidth() - rect.width - 20;
		rect.y = 100;
		propertyY = rect.y + 50;
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
		materialButton->update(rect.x + rect.width - animateButton->getWidth() - materialButton->getWidth() - 30, rect.y + 10);
		materialButton->draw();
	}

	drawTransformSliders(obj);

	/*int slidersMul = 3;
	if (!enableScaling)
	{
		slidersMul--;
	}
	if (!enableRotation)
	{
		slidersMul--;
	}*/

	//int y = rect.y + (slidersMul * position.getHeight()) + 90;
	int y = propertyY + transformGroup.getRealHeight() + 10;
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
	transformGroup.update(rect.x + offsetX, propertyY);
	transformGroup.drawOnToggled = [&](int x, int y)
	{
		position.update();
		rotation.update();
		scale.update();

		float fullHeight = 0;
		position.draw(x, y + fullHeight, propertyWidth, obj.getPosition());
		fullHeight += position.getHeight();

		if (enableRotation)
		{
			rotation.draw(x, y + fullHeight, propertyWidth, obj.getOrientationEuler());
			fullHeight += rotation.getHeight();
		}

		if (enableScaling)
		{
			scale.draw(x, y + fullHeight, propertyWidth, obj.getScale());
			fullHeight += scale.getHeight();
		}

		transformGroup.setFullHeight(fullHeight);
	};

	transformGroup.draw();
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
	propertyY = rect.y + 50;
}

void propertiesPanel::setHeight(int h)
{
	rect.height = h;
}
