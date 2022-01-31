#include "image.h"
#include <iostream>
#include "ofSystemUtils.h"
#include "object.h"

image::image(const object& objRef, ofFileDialogResult result) : component(objRef), size(0,0), im()
{
	if (result.bSuccess)
	{
		ofFile file(result.getPath());

		if (file.exists())
		{
			std::string fileExtension = ofToUpper(file.getExtension());

			if (fileExtension == "JPG" || fileExtension == "PNG")
			{
				im.load(result.getPath());
				size.x = im.getWidth();
				size.y = im.getHeight();
			}
		}
	}
}

void image::drawUI()
{
}

void image::draw()
{
	if (im.isAllocated())
	{
		im.draw(obj.position, size.x * obj.scale.x, size.y * obj.scale.y);
	}
}
