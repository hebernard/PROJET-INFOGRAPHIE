#pragma once
#include "objects/object.h"
#include "terrain/mapGenerator.h"
#include "ui/menuBar/menuBarButton.h"

class terrain : public object
{
public:
	terrain();

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);

private:
	mapGenerator mapGen;

	menuBarButton generateButton, seedButton;

	sliderProperty widthProp, heightProp, amplitudeProp, scaleProp;
};

