#pragma once
#include "objects/object.h"
#include "terrain/mapGenerator.h"
#include "ui/menuBar/menuBarButton.h"

class terrain : public object
{
public:
	terrain();

	void customDraw();
	void drawProperties(int x, int y, int width);

private:
	mapGenerator mapGen;

	menuBarButton generateButton, seedButton;
	inputProperty widthProp, heightProp, amplitudeProp;

	sliderProperty scaleProp;
};

