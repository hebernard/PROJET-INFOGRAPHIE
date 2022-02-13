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

protected:
	hierarchyButton* button;
};

