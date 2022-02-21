#pragma once
#include <iostream>
#include "ofMain.h"

class object;
class hierarchySmallButton;

class centeredSlider
{
public:
    glm::vec3 axis = glm::vec3(1, 0, 0);
    float value = 0;
    hierarchySmallButton* resetButton;

	centeredSlider(std::string text);

	void draw(int x, int y, int width, glm::vec3 xyz);

    void mouseDragged(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);

private:
    bool dragStarted = false;
    int thumbX;
    int thumbRadius = 10;
    int minX;
    int maxX;

    int current = 0;
    ofColor axisColor = ofColor::red;

	ofRectangle xyzRect, slider;
	std::string m_text;
    glm::vec2 textSize;


    std::string getDrawedValue(glm::vec3 xyz);

    void drawResetButton(int x, int y);
    void drawXYZRect(int x, int y);
    void drawSlider(int x, int y, int width);
    void drawValue(int x, int y, glm::vec3 xyz);
};

