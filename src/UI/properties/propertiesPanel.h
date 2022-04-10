#pragma once

#include "ofMain.h"
#include "centeredSlider.h"
#include "animation/ui/animationPanel.h"
#include "materials/materialPanel.h"

class object;
class hierarchySmallButton;

class propertiesPanel
{
public:
    function<void()> onUpdate;

    bool enableRotation = true;
    bool enableScaling = true;
    bool anchoredRight = true;

	propertiesPanel();
    ~propertiesPanel();

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

    void setPosition(int x, int y);
    void setHeight(int h);

private:
    object* m_obj;
    const int offsetX = 15;
    int propertyWidth;
    const float translationSpeed = 8;
    const float rotationSpeed = 40;
    const float scaleSpeed = 1.5f;

	ofRectangle rect;
	hierarchySmallButton* backButton;
	hierarchySmallButton* animateButton;
	hierarchySmallButton* materialButton;

    bool animationPanelVisible = false;
    animationPanel animPanel;

	centeredSlider position, rotation, scale;

    bool materialPanelVisible = false;
    materialPanel matPanel;

    ofFbo fbo;

    void drawTransformSliders(object& obj);
    void resetFocus();
};
