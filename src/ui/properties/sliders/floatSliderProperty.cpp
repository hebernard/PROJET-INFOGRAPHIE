#include "floatSliderProperty.h"

floatSliderProperty::floatSliderProperty(std::string label, float& ref, float min, float max, bool manualUpdate) :
	sliderBase(label, manualUpdate), 
	m_ref(ref),
	min(min),
	max(max)
{
	minS = ofToString(min);
	maxS = ofToString(max);

	// Initial update
	thumbPos = ofMap(m_ref, min, max, 0.f, 1.f, true);
	onValueUpdate();
}

void floatSliderProperty::onValueUpdate()
{
	float val = ofMap(thumbPos, 0.f, 1.f, min, max, true);
	value = ofToString(val);

	if (manualUpdate && onUpdate != 0)
	{
		onUpdate(val);
	}
	else
	{
		m_ref = val;
	}
}
