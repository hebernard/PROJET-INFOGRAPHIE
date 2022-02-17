#pragma once
#include <iostream>
#include "ofMain.h"

class object;

class centeredSlider
{
public:
    glm::vec3 axis = glm::vec3(1, 0, 0);
    float value = 0;

	centeredSlider(std::string text);

	void draw(int x, int y, glm::vec3 xyz);

    void mouseDragged(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);

private:
    bool dragStarted = false;
    int thumbX = 1110;
    int thumbRadius = 10;
    int minX = 990;
    int maxX = 1230;
    int current = 0;

	ofRectangle xyzRect, slider;
	std::string m_text;

    std::string getDrawedValue(glm::vec3 xyz);
};

