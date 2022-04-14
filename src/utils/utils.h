#pragma once
#include <queue>
#include <functional>
using Action = std::function<void()>;

class utils
{
public:
	static bool mousePressed;
	static bool mouseReleased;
	static bool rightMouseReleased;
	static bool isMouseOverUI;
	static int keyPressed;
	static bool onChange;

	// Vector of functions
	static std::queue<Action> drawOnTopQueue;
};
