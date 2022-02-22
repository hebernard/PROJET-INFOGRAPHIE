#pragma once

#include "ofMain.h"
#include "UI/hierarchy/hierarchyButton.h"
#include "mainTheme.h"

class object : public ofNode
{
public:
	bool markedForDeletion;
	bool isSelected;
	bool propertiesOpened;
	bool isVisible;

	object(hierarchyButton* btn) : button(btn), isSelected(false), markedForDeletion(false), propertiesOpened(false), isVisible(true) {}
	virtual ~object()
	{
		delete button;
	}

	virtual void customDraw()
	{
	}

	void drawWithTransformations()
	{
		ofPushMatrix();
		ofTranslate(getPosition());
		ofRotateXDeg(getOrientationEulerDeg().x);
		ofRotateYDeg(getOrientationEulerDeg().y);
		ofRotateZDeg(getOrientationEulerDeg().z);
		ofScale(getScale());

		if (isSelected)
		{
			ofPushStyle();
			ofNoFill();
			ofSetColor(mainTheme::color1());
			auto bbox = getBBox();
			ofDrawBox(0, 0, 0, bbox.x, bbox.y, bbox.z);
			ofPopStyle();
		}

		customDraw();
		ofPopMatrix();
	}
	
	void drawHierarchy(int x, int y)
	{
		button->update(x, y);
		button->draw();
	}

	virtual void drawProperties(int x, int y, int width)
	{
	}

	virtual glm::vec3 getCenter()
	{
		return getPosition();
	}

	/// <summary>
	/// Gets the bounding box of the object
	/// </summary>
	/// <returns>A 2D vector representing the width, height and depth of the box from the center point</returns>
	virtual glm::vec3 getBBox()
	{
		return glm::vec3();
	}

	std::string getName() const
	{
		return button->getLabel();
	}

protected:
	hierarchyButton* button;
};

