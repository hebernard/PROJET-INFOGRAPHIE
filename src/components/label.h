#pragma once

#include "ofxDatGuiComponent.h"
#include "ofxDatGui.h"

class label : public ofxDatGuiLabel
{
public:
	label(string label) : ofxDatGuiLabel(label)
	{
		setStripeVisible(false);
		setLabelUpperCase(false);
		setTheme(ofxDatGuiComponent::getTheme());
	}

	void setTheme(const ofxDatGuiTheme* theme)
	{
		setComponentStyle(theme);
	}

	void drawBackground() {}
};

