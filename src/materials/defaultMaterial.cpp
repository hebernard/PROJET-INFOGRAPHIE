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
		if (ref != nullptr)
		{
			ofLoadImage(ref->originalTexture, path);
			setFilter(ref->currentFilterIndex);
		}
	};

	imgProp.onImageCleared = [&]()
	{
		imgProp.resetPreview();
		if (ref != nullptr)
		{
			ref->originalTexture.clear();
			ref->filteredTexture.clear();
		}
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
	int propX = x + 15;
	int propW = width - 30;
	int propY = y + imgProp.getHeight();
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

void defaultMaterial::setObject(object& obj)
{
	materialBase::setObject(obj);
	// reset the preview upon changing objects
	if (!obj.originalTexture.isAllocated())
	{
		imgProp.resetPreview();
	}
	else
	{
		ofPixels pixels;
		obj.originalTexture.readToPixels(pixels);

		imgProp.setPreview(pixels);
	}

	ambientColor->set(ref->material.getAmbientColor());
	diffuseColor->set(ref->material.getDiffuseColor());
	emissiveColor->set(ref->material.getEmissiveColor());
	specularColor->set(ref->material.getSpecularColor());
	*shininess = ref->material.getShininess();

	ambientColorProp.forceUpdate();
	diffuseColorProp.forceUpdate();
	emissiveColorProp.forceUpdate();
	specularColorProp.forceUpdate();
	shininessProp.setMax(100);
	shininessProp.forceUpdateValue();

	filterProp.setSelected(ref->currentFilterIndex);
}

void defaultMaterial::setFilter(int index)
{
	if (ref != nullptr)
	{
		ref->currentFilterIndex = index;
		ofTexture tex = applyFilter(ref->originalTexture, filterType(index));
		if (tex.isAllocated())
		{
			ref->filteredTexture = tex;
		}
	}
}
