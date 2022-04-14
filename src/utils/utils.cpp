#include "utils.h"

bool utils::mousePressed;
bool utils::mouseReleased;
bool utils::rightMouseReleased;
bool utils::isMouseOverUI;
bool utils::isDropdownOpened;
int utils::keyPressed;
bool utils::onChange;

std::queue<Action> utils::drawOnTopQueue;
