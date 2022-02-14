#pragma once

#include "ofMain.h"
#include "UI/hierarchy/hierarchyButton.h"

class object : public ofNode
{
public:
	bool markedForDeletion;
	bool isSelected;

	object(hierarchyButton* btn) : button(btn), isSelected(false), markedForDeletion(false) {}
	virtual ~object()
	{
		delete button;
	}

	virtual void customDraw() {}
	void drawHierarchy(int x, int y)
	{
		button->update(x, y);
		button->draw();
	}

	virtual glm::vec3 getCenter()
	{
		return glm::vec3();
	}

	/// <summary>
	/// Gets the bounding box of the object
	/// </summary>
	/// <returns>A 2D vector representing the width, height and depth of the box from the center point</returns>
	virtual glm::vec3 getBBox()
	{
		return glm::vec3();
	}

protected:
	hierarchyButton* button;
};

