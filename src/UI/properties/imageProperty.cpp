#include "imageProperty.h"
#include "label.h"
#include "utils.h"
#include "panel.h"

imageProperty::imageProperty(std::string label) : m_label(label)
{
	importBox.height = 75;
	importBox.width = 150;
}

void imageProperty::draw(ofTexture& tex, int x, int y, int width)
{
	ofPushStyle();
	bool hovered = importBox.inside(ofGetMouseX(), ofGetMouseY());

	drawText(x, y + importBox.height - 5, m_label, 11);

	importBox.x = x + width - importBox.width;
	importBox.y = y;

	if (hovered && utils::mousePressed)
	{
		importImage(tex);
	}

	if (tex.isAllocated())
	{
		ofSetColor(mainTheme::fontColor());
		ofDrawRectangle(importBox.x - 1, importBox.y - 1, importBox.width + 2, importBox.height + 2);

		ofPixels pixels;
		tex.readToPixels(pixels);

		preview.setFromPixels(pixels);
		preview.resize(importBox.width, importBox.width / 2);

		ofSetColor(255);
		preview.draw(importBox.x, importBox.y);
	}
	else
	{
		ofSetColor(mainTheme::fontColor());
		ofDrawRectRounded(importBox.x - 1, importBox.y - 1, importBox.width + 2, importBox.height + 2, 14);

		ofSetColor(hovered ? mainTheme::panelButtonHoverColor() : mainTheme::toolBarButtonHoverColor());
		ofDrawRectRounded(importBox, 14);
	}

	auto size = label::getSize("Click to import", 10);
	drawText(importBox.x + importBox.width / 2 - size.x / 2, importBox.y + importBox.height - 5, "Click to import", 10);

	ofPopStyle();
}

int imageProperty::getHeight()
{
	return importBox.height;
}

void imageProperty::importImage(ofTexture& tex)
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Choisir un objet à importer");

	if (openFileResult.bSuccess)
	{
		ofFile file(openFileResult.getPath());

		if (file.exists())
		{
			std::string fileExtension = ofToUpper(file.getExtension());

			if (fileExtension == "JPG" || fileExtension == "PNG")
			{
				ofLoadImage(tex, file.path());
			}
			else
			{
				std::cout << "Invalid extension: " << fileExtension << std::endl;
			}
		}
	}
}
