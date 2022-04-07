#include "image.h"

image::image(std::string path) :
	object(new hierarchyButton(*this, "images/icons/image.png", "Image")),
	width(0),
	height(0),
	im(),
	widthInput("Width", width),
	heightInput("Height", height)
{
	im.load(path);
	width = im.getWidth() / 100;
	widthInput.forceUpdateValue();
	height = im.getHeight() / 100;
	heightInput.forceUpdateValue();

	cout << "Image loaded" << endl;

	canHaveMaterial = false;
}

void image::customDraw()
{
	if (im.isAllocated())
	{
		auto scale = getScale();
		float w = width * scale.x;
		float h = height * scale.y;
		im.draw(-w / 2, -h / 2, 0, w, h);
	}
}

void image::drawProperties(int x, int y, int width)
{
	// Dont call base class to not set filled property
	int offset = y;
	bboxCheckBox->draw(x, offset, width);
	offset += bboxCheckBox->getHeight() + 10;

	colorPicker->draw(x, offset, width);
	offset += 10 + colorPicker->getHeight();

	widthInput.draw(x, offset, width);
	offset += 10 + widthInput.getHeight();

	heightInput.draw(x, offset, width);
}

glm::vec3 image::getBBox()
{
	auto scale = getScale();
	return glm::vec3(width * scale.x, height * scale.y, 0);
}
