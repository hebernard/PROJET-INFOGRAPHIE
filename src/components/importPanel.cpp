#include "importPanel.h"
#include "label.h"
#include "panelButton.h"

importPanel::importPanel() :
	offsetX(20),
	title(new label("Import", "fonts/segoe_bold.ttf", 18, ofColor(63,63,63))),
	imagesSubtitle(new label("Images", "fonts/segoe_normal.ttf", 15, ofColor(63, 63, 63))),
	importImageBtn(new panelButton("images/icons/airplane.png"))
{
}

void importPanel::draw(int x, int y)
{
	int height = y + title->getHeight() + 14;
	title->setPosition(x + offsetX, height);
	title->draw();

	imagesSubtitle->setPosition(x + offsetX, height + 50);
	imagesSubtitle->draw();
	height += 50;

	ofSetColor(ofColor(238, 238, 238));
	importImageBtn->setPosition(x + offsetX, height + 15);
	importImageBtn->draw();
}

void importPanel::update()
{
	importImageBtn->update();
}
