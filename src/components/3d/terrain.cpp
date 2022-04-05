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
	mapGen.addRegion(ofColor::fromHex(0x030cb3), 0.15f);
	mapGen.addRegion(ofColor::fromHex(0x0411f4), 0.18f);
	mapGen.addRegion(ofColor::fromHex(0x3e48fc), 0.24f);

	// Sand
	mapGen.addRegion(ofColor::fromHex(0x937e3a), 0.26f);
	mapGen.addRegion(ofColor::fromHex(0xab9343), 0.30f);
	mapGen.addRegion(ofColor::fromHex(0xbca455), 0.34f);

	// Grass
	mapGen.addRegion(ofColor::fromHex(0x2a722d), 0.36f);
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

	float topLeftX = (width - 1) / -2.f;
	float topLeftY = (height - 1) / 2.f;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float value = heightMap[x][y];
			mesh.addVertex(ofPoint(topLeftX + x, topLeftY - y, value * value * amplitude));
			mesh.addColor(ofFloatColor(colorMap.getColor(x, y)));

			if (x < width - 1 && y < height - 1)
			{
				mesh.addIndex(x + y * width);
				mesh.addIndex((x + 1) + y * width);
				mesh.addIndex(x + (y + 1) * width);
				mesh.addIndex((x + 1) + y * width);
				mesh.addIndex((x + 1) + (y + 1) * width);
				mesh.addIndex(x + (y + 1) * width);
			}
		}
	}

	mesh.flatNormals();
}
