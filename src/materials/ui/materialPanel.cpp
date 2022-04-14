#include "materialPanel.h"
#include "ui/hierarchy/hierarchySmallButton.h"
#include "ui/panel.h"
#include "ui/label.h"
#include "utils/filtering.h"
#include "materials/defaultMaterial.h"
#include "materials/pbrMaterial.h"

materialPanel::materialPanel() :
	backButton(new hierarchySmallButton("images/icons/back.png")),
	materialDropdown("Material")
{
	rect.width = 300;
	rect.y = 100;

	materialDropdown.setElements({ "Default", "PBR" });
	materialDropdown.onClick = [&](int index)
	{
		if (ref != 0)
		{
			if (index == 0)
			{
				ref->material = new defaultMaterial();
				ref->matIndex = 0;
			}
			else if (index == 1)
			{
				ref->material = new pbrMaterial();
				ref->matIndex = 1;
			}
		}
	};
}

materialPanel::~materialPanel()
{
	delete backButton;
}

void materialPanel::draw()
{
	if (ref == nullptr)
	{
		return;
	}

	float propY = rect.y;
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	propY += 32;
	drawText(rect.x + 60, propY, ref->getName() + "/Material", 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	propY += 30;
	materialDropdown.draw(rect.x + 15, propY, rect.width - 30);

	propY += materialDropdown.getHeight() + 10;
	if (ref->material != nullptr)
	{
		ref->material->draw(rect.x + 15, propY, rect.width - 30);
	}
}

void materialPanel::setObject(object& obj)
{
	ref = &obj;
	materialDropdown.setSelected(ref->matIndex);
}
