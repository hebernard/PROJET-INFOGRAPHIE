#pragma once

#include "ofMain.h"
#include "ui/hierarchy/hierarchyButton.h"
#include "ui/mainTheme.h"
#include "ui/properties/checkBoxProperty.h"
#include "ui/properties/inputProperty.h"
#include "ui/properties/colorProperty.h"
#include "ui/properties/sliders/sliderProperty.h"
#include "animation/keyframe.h"
#include "materials/materialBase.h"
#include "materials/defaultMaterial.h"

class object : public ofNode
{
public:
	bool filled = true;
	bool showBBox = true;
	bool markedForDeletion;
	bool isSelected;
	bool propertiesOpened;
	bool isVisible;
	ofColor color = ofColor::white;

	// Animation
	bool canBeAnimated = true;
	std::vector<keyframe> keyframes;
	float animationMaxTime = 0;

	// Material
	bool canHaveMaterial = true;
	materialBase* material = new defaultMaterial();
	int matIndex = 0;

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
		delete bboxCheckBox;
		delete material;
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

		if (canHaveMaterial)
		{
			material->begin();
		}
		else
		{
			ofSetColor(color);
		}

		customDraw();

		if (canHaveMaterial) material->end();
		ofPopStyle();
		ofPopMatrix();
	}
	
	void drawHierarchy(int x, int y)
	{
		button->update(x, y);
		button->draw();
	}

	virtual void drawProperties(int x, int y, int width, int originX = 0, int originY = 0)
	{
		int offset = y;
		bboxCheckBox->draw(x, offset, width);
		offset += bboxCheckBox->getHeight() + 10;
		filledCheckBox->draw(x, offset, width);
		//offset += filledCheckBox->getHeight() + 10;
		//colorPicker->draw(x, offset, width);
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
		return filledCheckBox->getHeight() + /*10 + colorPicker->getHeight()*/ + 10 + bboxCheckBox->getHeight() + 10;
	}
};

