#include "label.h"
#include "ofMain.h"

std::vector<fontArgs*> label::fonts;

void drawText(int x, int y, std::string text, int fontSize, ofColor color, std::string path)
{
	auto font = label::getFont(path, fontSize);

	ofPushStyle();
	ofSetColor(color);
	font->drawString(text, x, y);
	ofPopStyle();
}

ofTrueTypeFont* label::getFont(std::string path, int fontSize)
{
	for (size_t i = 0; i < label::fonts.size(); i++)
	{
		auto args = label::fonts.at(i);
		if (args->path == path && args->font->getSize() == fontSize)
		{
			return args->font;
		}
	}

	// The font wasn't found, add it
	ofTrueTypeFont* font = new ofTrueTypeFont();
	font->load(path, fontSize);
	label::fonts.push_back(new fontArgs(path, font));

	std::cout << "Added new font: " << path << " with size " << fontSize << endl;

	return font;
}

glm::vec2 label::getSize(std::string text, int fontSize, std::string path)
{
	auto font = label::getFont(path, fontSize);
	return glm::vec2(font->stringWidth(text), font->stringHeight(text));
}

label::~label()
{
	for (auto i : fonts)
	{
		delete i;
	}
}
