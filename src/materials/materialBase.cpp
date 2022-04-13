#include "materialBase.h"

materialBase::materialBase(std::string name) : name(name), ref()
{
}

materialBase::~materialBase()
{
}

void materialBase::setObject(object& obj)
{
	ref = &obj;
}

std::string materialBase::getName()
{
	return name;
}
