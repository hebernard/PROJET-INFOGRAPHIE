#include "pbrMaterial.h"
#include "scene.h"

pbrMaterial::pbrMaterial() : materialBase("PBR"), shader(),
	diffuseProp("Diffuse Map"),
	metallicProp("Metallic Map"),
	roughnessProp("Roughness Map"),
	occlusionProp("Occlusion Map"),
	ambientColorProp("Ambient", ambientColor),
	diffuseColorProp("Diffuse", diffuseColor),
	specularColorProp("Specular", specularColor),
	brightnessSlider("Brightness", brightness, 0.f, 1.f),
	metallicSlider("Metallic", metallic, 0.f, 1.f),
	roughnessSlider("Roughness", roughness, 0.f, 1.f),
	occlusionSlider("Occlusion", occlusion, 0.f, 1.f),
	gammaSlider("Gamma", gamma, 0.f, 5.f),
	firstLight()
{
	shader.load("shaders/pbr_330");

	scene& s = s.getInstance();
	firstLight = &s.getFirstLight();

	diffuseProp.onImageImport = [&](string path)
	{
		diffuseTex.load(path);
		diffuseTex.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	};
	diffuseProp.onImageCleared = [&]()
	{
		diffuseProp.resetPreview();
		diffuseTex.clear();
	};

	metallicProp.onImageImport = [&](string path)
	{
		metallicTex.load(path);
		metallicTex.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	};
	metallicProp.onImageCleared = [&]()
	{
		metallicProp.resetPreview();
		metallicTex.clear();
	};

	roughnessProp.onImageImport = [&](string path)
	{
		roughnessTex.load(path);
		roughnessTex.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	};
	roughnessProp.onImageCleared = [&]()
	{
		roughnessProp.resetPreview();
		roughnessTex.clear();
	};

	occlusionProp.onImageImport = [&](string path)
	{
		occlusionTex.load(path);
		occlusionTex.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	};
	occlusionProp.onImageCleared = [&]()
	{
		occlusionProp.resetPreview();
		occlusionTex.clear();
	};
}

pbrMaterial::~pbrMaterial()
{
}

void pbrMaterial::draw(int x, int y, int width)
{
	float propY = y;

	diffuseProp.draw(x, propY, width);
	propY += diffuseProp.getHeight() + 10;

	metallicProp.draw(x, propY, width);
	propY += metallicProp.getHeight() + 10;

	roughnessProp.draw(x, propY, width);
	propY += roughnessProp.getHeight() + 10;

	occlusionProp.draw(x, propY, width);
	propY += occlusionProp.getHeight() + 10;

	/*ambientColorProp.draw(x, propY, width);
	propY += ambientColorProp.getHeight() + 10;

	diffuseColorProp.draw(x, propY, width);
	propY += diffuseColorProp.getHeight() + 10;

	specularColorProp.draw(x, propY, width);
	propY += specularColorProp.getHeight() + 10;*/

	brightnessSlider.draw(x, propY, width);
	propY += brightnessSlider.getHeight() + 10;

	metallicSlider.draw(x, propY, width);
	propY += metallicSlider.getHeight() + 10;

	roughnessSlider.draw(x, propY, width);
	propY += roughnessSlider.getHeight() + 10;

	occlusionSlider.draw(x, propY, width);
	propY += occlusionSlider.getHeight() + 10;

	gammaSlider.draw(x, propY, width);
}

void pbrMaterial::begin()
{
	shader.begin();
	if (diffuseTex.isAllocated())
	{
		shader.setUniformTexture("texture_diffuse", diffuseTex.getTexture(), 1);
	}
	if (metallicTex.isAllocated())
	{
		shader.setUniformTexture("texture_metallic", metallicTex.getTexture(), 2);
	}
	if (roughnessTex.isAllocated())
	{
		shader.setUniformTexture("texture_roughness", roughnessTex.getTexture(), 3);
	}
	if (occlusionTex.isAllocated())
	{
		shader.setUniformTexture("texture_occlusion", occlusionTex.getTexture(), 4);
	}

	shader.setUniform3f("material_color_ambient", ambientColor.r / 255.f, ambientColor.g / 255.f, ambientColor.b / 255.f);
	shader.setUniform3f("material_color_diffuse", diffuseColor.r / 255.f, diffuseColor.g / 255.f, diffuseColor.b / 255.f);
	shader.setUniform3f("material_color_specular", specularColor.r / 255.f, specularColor.g / 255.f, specularColor.b / 255.f);

	shader.setUniform1f("material_brightness", brightness);
	shader.setUniform1f("material_metallic", metallic);
	shader.setUniform1f("material_roughness", roughness);
	shader.setUniform1f("material_occlusion", occlusion);

	ofColor ambientColor = firstLight->li.getAmbientColor();
	shader.setUniform1f("light_intensity", 10.f);
	shader.setUniform3f("light_color", ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f);
	shader.setUniform3f("light_position", glm::vec4(firstLight->getPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	shader.setUniform1i("tone_mapping_toggle", false);
	shader.setUniform1f("tone_mapping_exposure", 1.0f);
	shader.setUniform1f("tone_mapping_gamma", gamma);
	shader.setUniform3f("material_fresnel_ior", 0.04f, 0.04f, 0.04f);
}

void pbrMaterial::end()
{
	shader.end();
}
