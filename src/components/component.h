#pragma once

class object;

class component
{
public:
	const object& obj;

	component(const object& objRef);
	virtual ~component() = default;

	virtual void drawUI();
	virtual void draw();
};

