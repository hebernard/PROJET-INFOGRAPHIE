#include "materialPanel.h"
#include "ui/hierarchy/hierarchySmallButton.h"
#include "ui/panel.h"
#include "ui/label.h"
#include "utils/filtering.h"

materialPanel::materialPanel() : backButton(new hierarchySmallButton("images/icons/back.png")), mat(new defaultMaterial())
{
	rect.width = 300;
	rect.y = 100;
}

materialPanel::~materialPanel()
{
	delete backButton;
}

void materialPanel::draw()
{
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, /*ref->getName() + */"/Material", 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	mat->draw(rect.x, rect.y, rect.width);
}

void materialPanel::setObject(object& obj)
{
	mat->setObject(obj);
}
