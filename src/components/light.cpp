#include "light.h"
#include "lightHierarchyButton.h"
#include "utils.h"

light::light(int id) :
    object(new lightHierarchyButton(*this, "images/icons/light.png", "Light", id != 0)),
    id(id),
    lightTypeProp(dropdownProperty("Light type")),
    ambientColorProp(colorProperty("Ambient", ambientColor)),
    diffuseColorProp(colorProperty("Diffuse", diffuseColor)),
    specularColorProp(colorProperty("Specular", specularColor))
{
    lightTypeProp.setElements({ "Point", "Directional", "Spot", "Area" });
    lightTypeProp.onClick = [&](int i) { setType(ofLightType(i)); };

    setType(ofLightType::OF_LIGHT_POINT);
}

void light::customDraw()
{
    // dont forget to set position of orientation of ofLight
    li.setPosition(getPosition());
    li.setOrientation(getOrientationEuler());

    if (li.getType() == ofLightType::OF_LIGHT_AREA)
    {
        li.setAreaLight(getScale().x, getScale().y);
    }

    // also dont forget to set color
    li.setAmbientColor(ambientColor);
    li.setDiffuseColor(diffuseColor);
    li.setSpecularColor(specularColor);

    li.draw();
}

void light::drawProperties(int x, int y, int width)
{
    int offset = y;
    lightTypeProp.draw(x, offset, width);
    offset += 10 + lightTypeProp.getHeight();

    ambientColorProp.draw(x, offset, width);
    ambientColorProp.interactable = !lightTypeProp.focused;
    offset += 10 + ambientColorProp.getHeight();

    diffuseColorProp.draw(x, offset, width);
    diffuseColorProp.interactable = !lightTypeProp.focused;
    offset += 10 + diffuseColorProp.getHeight();

    specularColorProp.draw(x, offset, width);
    specularColorProp.interactable = !lightTypeProp.focused;
    offset += 10 + specularColorProp.getHeight();
}

void light::setType(ofLightType type)
{
    cout << "Set Light Type to: ";
    switch (type)
    {
    case ofLightType::OF_LIGHT_AREA:
        // This light is for effects like an emissive surface
        li.setAreaLight(getScale().x, getScale().y);
        cout << "Ambient" << endl;
        break;

    case ofLightType::OF_LIGHT_DIRECTIONAL:
        li.setDirectional();
        cout << "Directional" << endl;
        break;

    case ofLightType::OF_LIGHT_POINT:
        li.setPointLight();
        cout << "Point" << endl;
        break;

    case ofLightType::OF_LIGHT_SPOT:
        li.setSpotlight();
        li.setSpotConcentration(2);
        li.setSpotlightCutOff(30);
        cout << "Spot" << endl;
        break;

    default:
        break;
    }
}
