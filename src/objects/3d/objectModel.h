#pragma once
#include "objects/object.h"
#include "ofxAssimpModelLoader.h"

class objectModel : public object
{
public:
	objectModel(std::string path);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

private:
	ofxAssimpModelLoader obj;
};