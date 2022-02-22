#pragma once
#include "ofRectangle.h"
#include "mainTheme.h"

void drawPanel(int x, int y, int width, int height, ofColor backgroundColor = mainTheme::panelColor());
void drawPanel(ofRectangle& rect, ofColor backgroundColor = mainTheme::panelColor());