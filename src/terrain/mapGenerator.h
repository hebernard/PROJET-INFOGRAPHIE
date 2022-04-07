#pragma once
#include "ofMain.h"

struct Region
{
	ofColor color;
	float height;
};

class mapGenerator : public ofThread
{
public:
	int width = 100;
	int height = 100;
	float scale = 200.f;
	int octaves = 5;
	float persistance = 0.5f;
	float lacunarity = 2.f;
	float amplitude = 30;
	int seed = ofRandom(100000);

	void addRegion(ofColor color, float height);
	void generateMesh();

	void newSeed();

	void draw(bool filled);

private:
	bool canDraw = false;
	ofMesh mesh;
	vector<Region> regions;

	vector<vector<float>> generateHeightMap(int width, int height);
	ofPixels generateColorMap(vector<vector<float>> heightMap);

	void threadedFunction();
};
