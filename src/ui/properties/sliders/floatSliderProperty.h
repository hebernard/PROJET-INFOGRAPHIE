#pragma once
#include "sliderBase.h"

class floatSliderProperty : public sliderBase
{
public:
	std::function<void(float)> onUpdate;

	floatSliderProperty(std::string label, float& ref, float min, float max);

protected:
	void onValueUpdate();

private:
	float& m_ref;

	float max;
	float min;
};

