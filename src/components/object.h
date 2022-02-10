#pragma once

#include "ofMain.h"
#include "UI/hierarchy/hierarchyButton.h"

class object : public ofNode
{
public:
	object(hierarchyButton* btn) : button(btn) {}
	virtual ~object() {}

	virtual void customDraw() {}
	virtual void drawHierarchy(int x, int y) {}
	virtual glm::vec3 getCenter()
	{
		return glm::vec3();
	}

protected:
	hierarchyButton* button;
};

