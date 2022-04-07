#pragma once
#include "objects/object.h"
#include "ofxAssimpModelLoader.h"

class objectModel : public object
{
public:
	objectModel(std::string path);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

private:
	ofxAssimpModelLoader obj;
};