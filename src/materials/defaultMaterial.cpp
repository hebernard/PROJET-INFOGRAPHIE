#include "defaultMaterial.h"
#include "utils/filtering.h"
#include "ui/panel.h"

defaultMaterial::defaultMaterial() : materialBase("Default"),
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
	imgProp.onImageImport = [&](string path)
	{
		ofLoadImage(originalTexture, path);
		setFilter(currentFilterIndex);
	};

	imgProp.onImageCleared = [&]()
	{
		imgProp.resetPreview();
		originalTexture.clear();
		filteredTexture.clear();
	};

	filterProp.setElements(getFilterTypes());
	filterProp.onClick = [&](int index) { defaultMaterial::setFilter(index); };
}

defaultMaterial::~defaultMaterial()
{
	delete ambientColor;
	delete diffuseColor;
	delete emissiveColor;
	delete specularColor;
	delete shininess;
}

void defaultMaterial::draw(int x, int y, int width)
{
	int propY = y;
	int offset = 15;

	imgProp.draw(x, propY, width);
	propY += imgProp.getHeight() + offset;

	if (originalTexture.isAllocated())
	{
		ambientColorProp.interactable = !filterProp.focused;
		diffuseColorProp.interactable = !filterProp.focused;
		emissiveColorProp.interactable = !filterProp.focused;
		specularColorProp.interactable = !filterProp.focused;

		filterProp.draw(x, propY, width);
		propY += filterProp.getHeight() + offset;
	}

	ambientColorProp.draw(x, propY, width);
	propY += ambientColorProp.getHeight() + offset;

	diffuseColorProp.draw(x, propY, width);
	propY += diffuseColorProp.getHeight() + offset;

	emissiveColorProp.draw(x, propY, width);
	propY += emissiveColorProp.getHeight() + offset;

	specularColorProp.draw(x, propY, width);
	propY += specularColorProp.getHeight() + offset;

	shininessProp.draw(x, propY, width);

	material.setAmbientColor(*ambientColor);
	material.setDiffuseColor(*diffuseColor);
	material.setEmissiveColor(*emissiveColor);
	material.setSpecularColor(*specularColor);
	material.setShininess(*shininess);
}

void defaultMaterial::begin()
{
	material.begin();
	if (filteredTexture.isAllocated())
	{
		filteredTexture.bind();
	}
}

void defaultMaterial::end()
{
	if (filteredTexture.isAllocated())
	{
		filteredTexture.unbind();
	}
	material.end();
}

void defaultMaterial::setFilter(int index)
{
	currentFilterIndex = index;
	ofTexture tex = applyFilter(originalTexture, filterType(index));
	if (tex.isAllocated())
	{
		filteredTexture = tex;
	}
}
