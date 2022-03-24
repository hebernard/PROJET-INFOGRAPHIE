#pragma once
#include "ofRectangle.h"
#include "mainTheme.h"

void drawPanel(int x, int y, int width, int height, ofColor backgroundColor = mainTheme::panelColor());
void drawPanel(ofRectangle& rect, ofColor backgroundColor = mainTheme::panelColor());
void drawInputPanel(int x, int y, int width, int height, bool hovered, bool focused);
void drawInputPanel(const ofRectangle& rect, bool hovered, bool focused);