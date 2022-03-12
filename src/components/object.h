#pragma once

#include "ofMain.h"
#include "UI/hierarchy/hierarchyButton.h"
#include "mainTheme.h"
#include "checkBoxProperty.h"
#include "colorProperty.h"
#include "keyframe.h"

class object : public ofNode
{
public:
	bool filled = false;
	bool showBBox = true;
	bool markedForDeletion;
	bool isSelected;
	bool propertiesOpened;
	bool isVisible;
	ofColor color = ofColor::white;

	std::vector<keyframe> keyframes;
	float animationMaxTime = 0;

	object(hierarchyButton* btn) : 
		button(btn), 
		isSelected(false), 
		markedForDeletion(false), 
		propertiesOpened(false), 
		isVisible(true),
		bboxCheckBox(new checkBoxProperty("Bounding Box", showBBox)),
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

		if (isSelected && showBBox)
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
		ofUnregisterMouseEvents(bboxCheckBox);
	}

	virtual void drawProperties(int x, int y, int width)
	{
		ofRegisterMouseEvents(filledCheckBox);
		ofRegisterMouseEvents(bboxCheckBox);
		int offset = y;
		bboxCheckBox->draw(x, offset, width);
		offset += bboxCheckBox->getHeight() + 10;
		filledCheckBox->draw(x, offset, width);
		offset += filledCheckBox->getHeight() + 10;
		colorPicker->draw(x, offset, width);
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
	checkBoxProperty* bboxCheckBox;
	colorProperty* colorPicker;

	int getPropertiesHeight()
	{
		return filledCheckBox->getHeight() + 10 + colorPicker->getHeight() + 10 + bboxCheckBox->getHeight() + 10;
	}
};

