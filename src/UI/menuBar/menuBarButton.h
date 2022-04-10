#pragma once
#include "ui/uiComponent.h"

class menuBarButton : public uiComponent
{
public:
	menuBarButton(std::string text, int textOffset = 10);

	void draw();

	void setLabel(std::string text);

private:
	int textOff;
	std::string m_text;
	glm::vec2 textSize;
};

