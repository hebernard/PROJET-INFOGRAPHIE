#pragma once
#include "ofMain.h"
#include "hierarchySmallButton.h"

class checkBoxProperty
{
public:
	checkBoxProperty(std::string label, bool& ref);
	~checkBoxProperty();

	void draw(int x, int y, int width);
	int getHeight();

	void mouseMoved(ofMouseEventArgs& args);
	void mouseDragged(ofMouseEventArgs& args);
	void mousePressed(ofMouseEventArgs& args);
	void mouseReleased(ofMouseEventArgs& args);
	void mouseScrolled(ofMouseEventArgs& args);
	void mouseEntered(ofMouseEventArgs& args);
	void mouseExited(ofMouseEventArgs& args);

private:
	ofRectangle rect;

	bool hovered = false;
	bool previousState;
	bool& m_ref;
	std::string m_label;
	glm::vec2 labelSize;

	ofImage icon;
	ofRectangle checkBox;

	void setIcon();
};

