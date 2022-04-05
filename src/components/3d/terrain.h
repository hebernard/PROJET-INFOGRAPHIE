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

	void generateMesh(int width, int height);

private:
	ofMesh mesh;

	mapGenerator mapGen;

	menuBarButton generateButton, seedButton;
	inputProperty widthProp, heightProp, amplitudeProp;

	float width = 100;
	float height = 100;
	float amplitude = 30;
};

