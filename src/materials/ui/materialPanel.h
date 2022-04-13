#pragma once
#include "ofMain.h"
#include "ui/properties/dropdownProperty.h"
#include "objects/object.h"

class hierarchySmallButton;

class materialPanel
{
public:
	hierarchySmallButton* backButton;

	materialPanel();
	~materialPanel();

	void draw();

	void setObject(object& obj);

private:
	ofRectangle rect;
	object* ref;

	dropdownProperty materialDropdown;
};

