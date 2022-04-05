#pragma once
#include "ofMain.h"

struct Region
{
	ofColor color;
	float height;
};

class mapGenerator
{
public:
	float scale = 200.f;
	int octaves = 5;
	float persistance = 0.5f;
	float lacunarity = 2.f;
	int seed = ofRandom(100000);

	void addRegion(ofColor color, float height);
	vector<vector<float>> generateHeightMap(int width, int height);
	ofPixels generateColorMap(vector<vector<float>> heightMap);

	void newSeed();

private:
	vector<Region> regions;
};
