#include "mapGenerator.h"

void mapGenerator::addRegion(ofColor color, float height)
{
	Region region;
	region.color = color;
	region.height = height;
	regions.push_back(region);
}

void mapGenerator::generateMesh()
{
	startThread();
}

vector<vector<float>> mapGenerator::generateHeightMap(int width, int height)
{
	ofSeedRandom(seed);

	vector<glm::vec2> octaveOffsets;
	for (int i = 0; i < octaves; i++)
	{
		int offsetX = ofRandom(100);
		int offsetY = ofRandom(100);
		octaveOffsets.push_back({ offsetX, offsetY });
	}

	if (scale <= 0)
	{
		scale = 0.0001f;
	}

	float maxNoiseHeight = -100000.f;
	float minNoiseHeight = 100000.f;

	vector<vector<float>> noiseMap;
	for (int x = 0; x < width; x++)
	{
		vector<float> temp;
		for (int y = 0; y < height; y++)
		{
			float amplitude = 1;
			float frequency = 1;
			float noiseHeight = 0;

			for (int i = 0; i < octaves; i++)
			{
				float sampleX = (x - width / 2) / scale * frequency + octaveOffsets[i].x;
				float sampleY = (y - height / 2) / scale * frequency + octaveOffsets[i].y;

				float perlinValue = ofNoise(sampleX, sampleY) * 2 - 1;
				noiseHeight += perlinValue * amplitude;

				amplitude *= persistance;
				frequency *= lacunarity;
			}

			if (noiseHeight > maxNoiseHeight)
			{
				maxNoiseHeight = noiseHeight;
			}
			else if (noiseHeight < minNoiseHeight)
			{
				minNoiseHeight = noiseHeight;
			}

			temp.push_back(noiseHeight);
		}

		noiseMap.push_back(temp);
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			noiseMap[x][y] = ofMap(noiseMap[x][y], minNoiseHeight, maxNoiseHeight, 0, 1);
		}
	}

	return noiseMap;
}

ofPixels mapGenerator::generateColorMap(vector<vector<float>> heightMap)
{
	int width = heightMap.size();
	int height = heightMap[0].size();

	ofPixels pixels;
	pixels.allocate(width, height, OF_IMAGE_COLOR);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			for (int i = 0; i < regions.size(); i++)
			{
				if (heightMap[x][y] <= regions[i].height)
				{
					ofColor color = regions[i].color;
					if (i != 0 && i != regions.size() - 1)
					{
						color = regions[i - 1].color;
						color = color.lerp(regions[i].color, ofMap(heightMap[x][y], regions[i -1].height, regions[i].height, 0, 1));
					}
					pixels.setColor(x, y, color);
					break;
				}
			}
		}
	}

	return pixels;
}

void mapGenerator::threadedFunction()
{
	if (width <= 0 || height <= 0) return;
	mesh.clear();

	auto heightMap = generateHeightMap(width, height);
	auto colorMap = generateColorMap(heightMap);

	float topLeftX = (width - 1) / -2.f;
	float topLeftY = (height - 1) / 2.f;

	int vertexIndex = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float value = heightMap[x][y];
			mesh.addVertex(ofPoint(topLeftX + x, topLeftY - y, value * value * amplitude));
			mesh.addColor(ofFloatColor(colorMap.getColor(x, y)));

			if (x < width - 1 && y < height - 1)
			{
				mesh.addIndex(vertexIndex);
				mesh.addIndex(vertexIndex + width + 1);
				mesh.addIndex(vertexIndex + width);

				mesh.addIndex(vertexIndex + width + 1);
				mesh.addIndex(vertexIndex);
				mesh.addIndex(vertexIndex + 1);
			}

			vertexIndex++;
		}
	}

	mesh.flatNormals();
}

void mapGenerator::newSeed()
{
	seed = ofRandom(1000000);
}

void mapGenerator::draw(bool filled)
{
	if (!isThreadRunning())
	{
		if (filled)
		{
			mesh.drawFaces();
		}
		else
		{
			mesh.drawWireframe();
		}
	}
}
