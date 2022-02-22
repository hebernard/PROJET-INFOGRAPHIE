#pragma once

#include "ofMain.h"
#include "centeredSlider.h"

class object;
class hierarchySmallButton;

class propertiesPanel
{
public:
	propertiesPanel();

	void draw(object& obj);

    //We need to declare all this mouse events methods to be able to listen to mouse events.
    //All this must be declared even if we are just going to use only one of this methods.
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args);
    void mouseEntered(ofMouseEventArgs& args);
    void mouseExited(ofMouseEventArgs& args);

private:
    const int translationSpeed = 5;
    const int rotationSpeed = 30;
    const int scaleSpeed = 1;

	ofRectangle rect;
	hierarchySmallButton* backButton;

	centeredSlider position, rotation, scale;

    void resetFocus();
};
