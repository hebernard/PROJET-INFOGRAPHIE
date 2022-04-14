#pragma once
#include <vector>
#include <iostream>
#include "ofTrueTypeFont.h"
#include "ui/mainTheme.h"

struct fontArgs
{
public:
	std::string path;
	ofTrueTypeFont* font;

	fontArgs(std::string path, ofTrueTypeFont* font)
	{
		this->path = path;
		this->font = font;
	}

	~fontArgs()
	{
		delete font;
	}
};

class label
{
public:
	static std::vector<fontArgs*> fonts;

	static ofTrueTypeFont* getFont(std::string path, int fontSize);
	static glm::vec2 getSize(std::string text, int fontSize, std::string path = mainTheme::fontMediumPath);

private:
	~label();
};

void drawText(int x, int y, std::string text, int fontSize, ofColor color = mainTheme::fontColor(), std::string path = mainTheme::fontMediumPath);
void drawTextCentered(int x, int y, int rectHeight, std::string text, int fontSize, ofColor color = mainTheme::fontColor(), std::string path = mainTheme::fontMediumPath);
