#pragma once
#include <iostream>
#include "ofRectangle.h"

class materialBase
{
public:
	materialBase(std::string name);
	virtual ~materialBase();

	virtual void draw(int x, int y, int width) = 0;

	virtual void begin() = 0;
	virtual void end() = 0;

	std::string getName();

private:
	std::string name;
};
