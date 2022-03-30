#pragma once
#include "hierarchyButton.h"

class lightHierarchyButton : public hierarchyButton
{
public:
	lightHierarchyButton(object& obj, std::string path, std::string label, bool isSecondary);
	~lightHierarchyButton();

	void update(int x, int y);
	void draw();

	void setIcon(string path);
	void setLabel(string label);

private:
	bool secondary;
	hierarchySmallButton* addLightButton;
};

