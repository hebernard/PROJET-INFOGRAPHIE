#pragma once
#include "sliderBase.h"

class intSliderProperty : public sliderBase
{
public:
	std::function<void(int)> onUpdate;

	intSliderProperty(std::string label, int& ref, int min, int max);

protected:
	void onValueUpdate();

private:
	int& m_ref;

	int min;
	int max;
};

