#include "materialPanel.h"
#include "hierarchySmallButton.h"
#include "panel.h"
#include "label.h"

materialPanel::materialPanel() :
	backButton(new hierarchySmallButton("images/icons/back.png")),
	imgProp(imageProperty("Texture"))
{
	rect.width = 300;
	rect.y = 100;
}

materialPanel::~materialPanel()
{
}

void materialPanel::draw(object& obj)
{
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, obj.getName() + "/Material", 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	int propX = rect.x + 15;
	int propW = rect.width - 30;

	imgProp.draw(obj.texture, propX, rect.y + imgProp.getHeight(), propW);
}
