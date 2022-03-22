#include "light.h"

light::light() : object(new hierarchyButton(*this, "images/icons/light.png", "Light"))
{

    isEnabled = true;
    hideLight = false;

    oscillationFrequency = 7500;
    oscillationAmplitude = 32.0f;

    // désactiver le matériau par défaut du modèle //teapot.disableMaterials();

    shaderColorFill.load("shaders/color_fill_330_vs.glsl", "shaders/color_fill_330_fs.glsl");
    shaderLambert.load("shaders/lambert_330_vs.glsl", "shaders/lambert_330_fs.glsl");
    shaderGouraud.load("shaders/gouraud_330_vs.glsl", "shaders/gouraud_330_fs.glsl");
    shaderPhong.load("shaders/phong_330_vs.glsl", "shaders/phong_330_fs.glsl");
    shaderBlinnPhong.load("shaders/blinn_phong_330_vs.glsl", "shaders/blinn_phong_330_fs.glsl");
    // shader actif au lancement de la scène
    activeShader = ShaderType::none;

    color = glm::vec3(1.0f, 1.0f, 1.0f);
    colorAmbient = glm::vec3(0.1f, 0.1f, 0.1f);
    colorDiffuse = glm::vec3(0.6f, 0.6f, 0.6f);
    colorSpecular = glm::vec3(1.0f, 1.0f, 0.0f);

    activeType = LightType::ambient;

    ambientColor = ofColor(191, 191, 191);
    diffuseColor = ofColor(191, 191, 191);
    specularColor = ofColor(191, 191, 191);

}

void light::update()
{
    // mise à jour d'une valeur numérique animée par un oscillateur
    float oscillation = oscillate(ofGetElapsedTimeMillis(), oscillationFrequency, oscillationAmplitude) + oscillationAmplitude;

    // passer les attributs uniformes au shader de sommets
    if (isActiveShader) {
        switch (activeShader)
        {
        case ShaderType::none:
            break;

        case ShaderType::color_fill:
            shaderName = "Color Fill";
            shader = &shaderColorFill;
            shader->begin();
            shader->setUniform3f("color", color.r, color.g, color.b);
            shader->end();
            break;

        case ShaderType::lambert:
            shaderName = "Lambert";
            shader = &shaderLambert;
            shader->begin();
            shader->setUniform3f("color_ambient", colorAmbient.r, colorAmbient.g, colorAmbient.b);
            shader->setUniform3f("color_diffuse", colorDiffuse.r, colorDiffuse.g, colorDiffuse.b);
            shader->setUniform3f("light_position", glm::vec4(li.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader->end();
            break;

        case ShaderType::gouraud:
            shaderName = "Gouraud";
            shader = &shaderGouraud;
            shader->begin();
            shader->setUniform3f("color_ambient", colorAmbient.r, colorAmbient.g, colorAmbient.b);
            shader->setUniform3f("color_diffuse", colorDiffuse.r, colorDiffuse.g, colorDiffuse.b);
            shader->setUniform3f("color_specular", colorSpecular.r, colorSpecular.g, colorSpecular.b);
            shader->setUniform1f("brightness", oscillation);
            shader->setUniform3f("light_position", glm::vec4(li.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader->end();
            break;

        case ShaderType::phong:
            shaderName = "Phong";
            shader = &shaderPhong;
            shader->begin();
            shader->setUniform3f("color_ambient", colorAmbient.r, colorAmbient.g, colorAmbient.b);
            shader->setUniform3f("color_diffuse", colorDiffuse.r, colorDiffuse.g, colorDiffuse.b);
            shader->setUniform3f("color_specular", colorSpecular.r, colorSpecular.g, colorSpecular.b);
            shader->setUniform1f("brightness", oscillation);
            shader->setUniform3f("light_position", glm::vec4(li.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader->end();
            break;

        case ShaderType::blinn_phong:
            shaderName = "Blinn-Phong";
            shader = &shaderBlinnPhong;
            shader->begin();
            shader->setUniform3f("color_ambient", colorAmbient.r, colorAmbient.g, colorAmbient.b);
            shader->setUniform3f("color_diffuse", colorDiffuse.r, colorDiffuse.g, colorDiffuse.b);
            shader->setUniform3f("color_specular", colorSpecular.r, colorSpecular.g, colorSpecular.b);
            shader->setUniform1f("brightness", oscillation);
            shader->setUniform3f("light_position", glm::vec4(li.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader->end();
            break;

        default:
            break;
        }
    }
    else {
        switch (activeType)
        {
        case LightType::ambient:
            li.setAmbientColor(ambientColor);
            break;

        case LightType::directional:
            li.setDiffuseColor(diffuseColor);
            li.setSpecularColor(specularColor);
            break;

        case LightType::point:
            li.setDiffuseColor(diffuseColor);
            li.setSpecularColor(specularColor);
            break;

        case LightType::spot:
            li.setDiffuseColor(diffuseColor);
            li.setSpecularColor(specularColor);
            li.setSpotConcentration(2);
            li.setSpotlightCutOff(30);
            break;

        default:
            break;
        }
    }
}

void light::customDraw()
{
    if (!hideLight) {
        li.draw();
    }
}

ShaderType light::getIlluminationModel()
{
	return activeShader;
}

void light::setIlluminationModel(ShaderType model)
{
    isActiveShader = true;
    activeShader = model;
}

LightType light::getType()
{
	return activeType;
}

void light::setType(LightType type)
{
    isActiveShader = false;
    activeType = type;

    switch (type)
    {
    case LightType::ambient:
        li.setAmbientColor(ambientColor);
        break;

    case LightType::directional:
        li.setAmbientColor(0);
        li.setDirectional();
        break;

    case LightType::point:
        li.setAmbientColor(0);
        li.setPointLight();
        break;

    case LightType::spot:
        li.setAmbientColor(0);
        li.setSpotConcentration(2);
        li.setSpotlightCutOff(30);
        li.setSpotlight();
        break;

    default:
        break;
    }
}

void light::hide()
{
    hideLight = !hideLight;
}


float light::oscillate(float time, float frequency, float amplitude)
{
    return sinf(time * 2.0f * PI / frequency) * amplitude;
}
