#include "sliderProperty.h"
#include "ui/label.h"

sliderProperty::sliderProperty(std::string label, float& ref, float min, float max, bool manualUpdate) : slider(new floatSliderProperty(label, ref, min, max, manualUpdate))
{
	dynamic_cast<floatSliderProperty&>(*slider).onUpdate = onUpdate;
}

sliderProperty::sliderProperty(std::string label, int& ref, int min, int max, bool manualUpdate) : slider(new intSliderProperty(label, ref, min, max, manualUpdate))
{
	dynamic_cast<intSliderProperty&>(*slider).onUpdate = onUpdate;
}

sliderProperty::~sliderProperty()
{
	delete slider;
}

void sliderProperty::draw(int x, int y, int width)
{
	slider->draw(x, y, width);
}

float sliderProperty::getHeight()
{
	return slider->getHeight();
}
