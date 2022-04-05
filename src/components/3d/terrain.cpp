#include "terrain.h"

terrain::terrain() : 
	object(new hierarchyButton(*this, "images/icons/terrain.png", "Terrain")),
	generateButton("Update"),
	seedButton("Generate new seed"),
	widthProp(inputProperty("Width", width)),
	heightProp(inputProperty("Height", height)),
	amplitudeProp(inputProperty("Amplitude", amplitude))
{
	canHaveMaterial = true;
	canBeAnimated = false;

	setOrientation({ -90, 0, 0 });

	// Adding the different colors for the heights
	// Water
	mapGen.addRegion(ofColor::fromHex(0x030cb3), 0.1f);
	mapGen.addRegion(ofColor::fromHex(0x0411f4), 0.14f);
	mapGen.addRegion(ofColor::fromHex(0x3e48fc), 0.18f);

	// Sand
	mapGen.addRegion(ofColor::fromHex(0x937e3a), 0.2f);
	mapGen.addRegion(ofColor::fromHex(0xab9343), 0.24f);
	mapGen.addRegion(ofColor::fromHex(0xbca455), 0.28f);

	// Grass
	mapGen.addRegion(ofColor::fromHex(0x2a722d), 0.32f);
	mapGen.addRegion(ofColor::fromHex(0x266629), 0.42f);
	mapGen.addRegion(ofColor::fromHex(0x215b24), 0.46f);

	// Rock
	mapGen.addRegion(ofColor::fromHex(0x533702), 0.53f);
	mapGen.addRegion(ofColor::fromHex(0x4a3102), 0.62f);
	mapGen.addRegion(ofColor::fromHex(0x422c01), 0.92f);

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	generateMesh(width, height);

	generateButton.onButtonEvent([&](auto e)
	{
		generateMesh(width, height);
	});

	seedButton.onButtonEvent([&](auto e)
	{
		mapGen.newSeed();
		generateMesh(width, height);
	});

	widthProp.forceUpdateValue(500);
	heightProp.forceUpdateValue(500);
	amplitudeProp.forceUpdateValue(500);
}

void terrain::customDraw()
{
	ofPushMatrix();
	ofScale(0.5f);
	if (filled)
	{
		mesh.drawFaces();
	}
	else
	{
		mesh.drawWireframe();
	}
	ofPopMatrix();
}

void terrain::drawProperties(int x, int y, int width)
{
	int offset = y;
	filledCheckBox->draw(x, offset, width);
	offset += filledCheckBox->getHeight() + 10;

	widthProp.draw(x, offset, width);
	offset += widthProp.getHeight() + 10;

	heightProp.draw(x, offset, width);
	offset += heightProp.getHeight() + 10;

	amplitudeProp.draw(x, offset, width);
	offset += amplitudeProp.getHeight() + 10;

	generateButton.setWidth(width);
	generateButton.update(x, offset);
	generateButton.draw(10);
	offset += generateButton.getHeight() + 10;

	seedButton.setWidth(width);
	seedButton.update(x, offset);
	seedButton.draw(10);
}

void terrain::generateMesh(int width, int height)
{
	auto heightMap = mapGen.generateHeightMap(width, height);
	auto colorMap = mapGen.generateColorMap(heightMap);

	mesh.clear();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			mesh.addVertex(ofPoint(x - width / 2, y - height / 2));
			mesh.addColor(ofFloatColor(colorMap.getColor(x, y)));
		}
	}

	for (int x = 0; x < width - 1; x++)
	{
		for (int y = 0; y < height - 1; y++)
		{
			mesh.addIndex(x + y * width);
			mesh.addIndex((x + 1) + y * width);
			mesh.addIndex(x + (y + 1) * width);
			mesh.addIndex((x + 1) + y * width);
			mesh.addIndex((x + 1) + (y + 1) * width);
			mesh.addIndex(x + (y + 1) * width);
		}
	}

	int count = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			ofVec3f position = mesh.getVertex(count);
			float value = heightMap[x][y];
			position.z = value * value * amplitude;
			mesh.setVertex(count, position);
			count++;
		}
	}

	mesh.flatNormals();
}
