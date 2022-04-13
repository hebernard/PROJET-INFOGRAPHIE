#pragma once
#include <iostream>
#include "ofRectangle.h"
#include "objects/object.h"

class materialBase
{
public:
	materialBase(std::string name);
	virtual ~materialBase();

	virtual void draw(int x, int y, int width) = 0;

	virtual void setObject(object& obj);

	std::string getName();

protected:
	object* ref;

private:
	std::string name;
};
