#pragma once

class label;
class panelButton;

class importPanel
{
public:
	importPanel();
	void draw(int x, int y);
	void update();

private:
	int offsetX;
	label* title;
	label* imagesSubtitle;
	panelButton* importImageBtn;
};

