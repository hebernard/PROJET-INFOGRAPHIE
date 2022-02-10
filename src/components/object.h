#pragma once

#include "ofMain.h"
#include "UI/hierarchy/hierarchyButton.h"

class object : public ofNode
{
public:
	bool isSelected;

	object(hierarchyButton* btn) : button(btn), isSelected(false) {}
	virtual ~object() {}

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

