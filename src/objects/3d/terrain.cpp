#include "terrain.h"

terrain::terrain() : 
	object(new hierarchyButton(*this, "images/icons/terrain.png", "Terrain")),
	generateButton("Update", 10),
	seedButton("Generate new seed", 12),
	widthProp(sliderProperty("Width", mapGen.width, 2, 1000)),
	heightProp(sliderProperty("Height", mapGen.height, 2, 1000)),
	amplitudeProp(sliderProperty("Amplitude", mapGen.amplitude, 1, 100)),
	scaleProp(sliderProperty("Scale", mapGen.scale, 0.f, 500.f))
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

	mapGen.generateMesh();

	generateButton.setLabel("Update (" + ofToString(mapGen.seed) + ")");

	generateButton.onClick = [&]()
	{
		mapGen.generateMesh();
	};

	seedButton.onClick = [&]()
	{
		mapGen.newSeed();
		generateButton.setLabel("Update (" + ofToString(mapGen.seed) + ")");
		mapGen.generateMesh();
	};
}

void terrain::customDraw()
{
	ofPushMatrix();
	ofScale(0.5f);
	mapGen.draw(filled);
	ofPopMatrix();
}

void terrain::drawProperties(int x, int y, int width, int originX, int originY)
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

	scaleProp.draw(x, offset, width);
	offset += scaleProp.getHeight() + 10;

	generateButton.setWidth(width);
	generateButton.update(x, offset, originX, originY);
	generateButton.draw();
	offset += generateButton.getHeight() + 10;

	seedButton.setWidth(width);
	seedButton.update(x, offset, originX, originY);
	seedButton.draw();
}
