#pragma once

#include "ofMain.h"
#include "UI/hierarchy/hierarchyButton.h"
#include "mainTheme.h"
#include "checkBoxProperty.h"
#include "colorProperty.h"

class object : public ofNode
{
public:
	bool filled = false;
	bool markedForDeletion;
	bool isSelected;
	bool propertiesOpened;
	bool isVisible;
	ofColor color = ofColor::white;

	object(hierarchyButton* btn) : 
		button(btn), 
		isSelected(false), 
		markedForDeletion(false), 
		propertiesOpened(false), 
		isVisible(true),
		filledCheckBox(new checkBoxProperty("Filled", filled)),
		colorPicker(new colorProperty("Color", color))
	{
	}
	
	virtual ~object()
	{
		delete button;
		delete filledCheckBox;
		delete colorPicker;
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

		ofPushStyle();
		if (filled)
		{
			ofFill();
		}
		else
		{
			ofNoFill();
		}
		ofSetColor(color);
		customDraw();
		ofPopStyle();
		ofPopMatrix();
	}
	
	void drawHierarchy(int x, int y)
	{
		button->update(x, y);
		button->draw();
		ofUnregisterMouseEvents(filledCheckBox);
	}

	virtual void drawProperties(int x, int y, int width)
	{
		ofRegisterMouseEvents(filledCheckBox);
		filledCheckBox->draw(x, y, width);
		colorPicker->draw(x, y + filledCheckBox->getHeight() + 10, width);
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
	checkBoxProperty* filledCheckBox;
	colorProperty* colorPicker;

	int getPropertiesHeight()
	{
		return filledCheckBox->getHeight() + 10 + colorPicker->getHeight() + 10;
	}
};

