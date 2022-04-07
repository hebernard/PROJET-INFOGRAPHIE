#include "utils.h"

bool utils::mousePressed;
bool utils::mouseReleased;
bool utils::rightMouseReleased;
bool utils::isMouseOverUI;
int utils::keyPressed;

std::queue<Action> utils::drawOnTopQueue;
