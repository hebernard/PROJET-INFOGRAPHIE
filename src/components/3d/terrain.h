#pragma once
#include "object.h"
#include "terrain/mapGenerator.h"
#include "UI/menuBar/menuBarButton.h"
#include "inputProperty.h"

class terrain : public object
{
public:
	terrain();

	void customDraw();
	void drawProperties(int x, int y, int width);

private:
	mapGenerator mapGen;

	menuBarButton generateButton, seedButton;
	inputProperty widthProp, heightProp, amplitudeProp, scaleProp;
};

