#include "materialPanel.h"
#include "hierarchySmallButton.h"
#include "panel.h"
#include "label.h"
#include "filtering.h"

materialPanel::materialPanel() :
	backButton(new hierarchySmallButton("images/icons/back.png")),
	imgProp(imageProperty("Texture")),
	filterProp(dropdownProperty("Filtering")),
	ambientColor(new ofColor(refMat.getAmbientColor())),
	diffuseColor(new ofColor(refMat.getDiffuseColor())),
	emissiveColor(new ofColor(refMat.getEmissiveColor())),
	specularColor(new ofColor(refMat.getSpecularColor())),
	ambientColorProp(colorProperty("Ambient", *ambientColor)),
	diffuseColorProp(colorProperty("Diffuse", *diffuseColor)),
	emissiveColorProp(colorProperty("Emissive", *emissiveColor)),
	specularColorProp(colorProperty("Specular", *specularColor)),
	shininess(new float(refMat.getShininess())),
	shininessProp(inputProperty("Shininess", *shininess))
{
	rect.width = 300;
	rect.y = 100;

	imgProp.onImageImport = [&](string path)
	{
		if (ref != nullptr)
		{
			ofLoadImage(ref->originalTexture, path);
			setFilter(currentFilter);
		}
	};

	filterProp.setElements(getFilterTypes());
	filterProp.onClick = [&](int index) { materialPanel::setFilter(index); };
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

void materialPanel::draw()
{
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, ref->getName() + "/Material", 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	int propX = rect.x + 15;
	int propW = rect.width - 30;
	int propY = rect.y + imgProp.getHeight();
	int offset = 15;

	imgProp.draw(propX, propY, propW);
	propY += imgProp.getHeight() + offset;

	if (ref->originalTexture.isAllocated())
	{
		ambientColorProp.interactable = !filterProp.focused;
		diffuseColorProp.interactable = !filterProp.focused;
		emissiveColorProp.interactable = !filterProp.focused;
		specularColorProp.interactable = !filterProp.focused;

		filterProp.draw(propX, propY, propW);
		propY += filterProp.getHeight() + offset;
	}

	ambientColorProp.draw(propX, propY, propW);
	propY += ambientColorProp.getHeight() + offset;

	diffuseColorProp.draw(propX, propY, propW);
	propY += diffuseColorProp.getHeight() + offset;

	emissiveColorProp.draw(propX, propY, propW);
	propY += emissiveColorProp.getHeight() + offset;

	specularColorProp.draw(propX, propY, propW);
	propY += specularColorProp.getHeight() + offset;

	shininessProp.draw(propX, propY, propW);

	ref->material.setAmbientColor(*ambientColor);
	ref->material.setDiffuseColor(*diffuseColor);
	ref->material.setEmissiveColor(*emissiveColor);
	ref->material.setSpecularColor(*specularColor);
	ref->material.setShininess(*shininess);
}

void materialPanel::setObject(object& obj)
{
	ref = &obj;
}

void materialPanel::setFilter(int index)
{
	currentFilter = index;
	if (ref != nullptr)
	{
		ofTexture tex = applyFilter(ref->originalTexture, filterType(index));
		if (tex.isAllocated())
		{
			ref->filteredTexture = tex;
		}
	}
}
