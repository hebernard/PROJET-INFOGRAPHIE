#pragma once

#include "ofxDatGuiComponent.h"

class fontNormal : public ofxDatGuiTheme
{
public:
	fontNormal()
	{
		font.size = 12;
		font.file = "fonts\\segoe_normal.ttf";
		init();
	}
};

