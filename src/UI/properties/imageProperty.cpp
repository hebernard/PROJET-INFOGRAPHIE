#include "imageProperty.h"
#include "label.h"
#include "utils.h"
#include "panel.h"

imageProperty::imageProperty(std::string label) : m_label(label)
{
	importBox.height = 75;
	importBox.width = 150;

	addIcon.load("images/icons/add_camera.png");
	addIcon.resize(50, 50);
}

void imageProperty::draw(ofTexture& tex, int x, int y, int width)
{
	bool hovered = importBox.inside(ofGetMouseX(), ofGetMouseY());

	drawText(x, y + importBox.height - 5, m_label, 11);

	importBox.x = x + width - importBox.width;
	importBox.y = y;

	if (hovered)
	{
		drawPanel(importBox, mainTheme::panelButtonHoverColor());

		if (utils::mousePressed)
		{
			importImage(tex);
		}
	}
	else
	{
		drawPanel(importBox);
	}

	if (!tex.isAllocated() && addIcon.isAllocated())
	{
		addIcon.draw(importBox.x + importBox.width / 2 - addIcon.getWidth() / 2, importBox.y + importBox.height / 2 - addIcon.getHeight() / 2);
	}
	else if (tex.isAllocated())
	{
		ofPixels pixels;
		tex.readToPixels(pixels);

		preview.setFromPixels(pixels);
		preview.resize(importBox.width, importBox.width / 2);

		preview.draw(importBox.x, importBox.y);
	}
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
