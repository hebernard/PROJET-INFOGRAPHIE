#include "materialBase.h"

materialBase::materialBase(std::string name) : name(name)
{
}

materialBase::~materialBase()
{
}

std::string materialBase::getName()
{
	return name;
}
