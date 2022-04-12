#include "intSliderProperty.h"

intSliderProperty::intSliderProperty(std::string label, int& ref, int min, int max) : 
	sliderBase(label), 
	m_ref(ref),
	min(min),
	max(max)
{
	minS = ofToString(min);
	maxS = ofToString(max);

	// Initial update
	thumbPos = ofMap(m_ref, min, max, 0, 1, true);
	onValueUpdate();
}

void intSliderProperty::onValueUpdate()
{
	int val = ofMap(thumbPos, 0, 1, min, max, true);
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

