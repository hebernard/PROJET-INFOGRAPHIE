#include "materialPanel.h"
#include "hierarchySmallButton.h"
#include "panel.h"
#include "label.h"

materialPanel::materialPanel() :
	backButton(new hierarchySmallButton("images/icons/back.png")),
	imgProp(imageProperty("Texture")),
	ambientColor(new ofColor(refMat.getAmbientColor())),
	diffuseColor(new ofColor(refMat.getDiffuseColor())),
	emissiveColor(new ofColor(refMat.getEmissiveColor())),
	specularColor(new ofColor(refMat.getSpecularColor())),
	shininess(new float(refMat.getShininess()))
{
	rect.width = 300;
	rect.y = 100;
}

materialPanel::~materialPanel()
{
	delete backButton;
	delete ambientColor;
	delete diffuseColor;
	delete emissiveColor;
	delete specularColor;
	delete shininess;
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
	int propY = rect.y + imgProp.getHeight();
	int offset = 15;

	imgProp.draw(obj.texture, propX, propY, propW);

	propY += imgProp.getHeight() + offset;
	ambientColorProp.draw(propX, propY, propW);

	propY += ambientColorProp.getHeight() + offset;
	diffuseColorProp.draw(propX, propY, propW);

	propY += diffuseColorProp.getHeight() + offset;
	emissiveColorProp.draw(propX, propY, propW);

	propY += emissiveColorProp.getHeight() + offset;
	specularColorProp.draw(propX, propY, propW);

	propY += specularColorProp.getHeight() + offset;
	shininessProp.draw(propX, propY, propW);

	obj.material.setAmbientColor(*ambientColor);
	obj.material.setDiffuseColor(*diffuseColor);
	obj.material.setEmissiveColor(*emissiveColor);
	obj.material.setSpecularColor(*specularColor);
	obj.material.setShininess(*shininess);
}
