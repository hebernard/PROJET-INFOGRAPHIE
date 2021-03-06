#include "light.h"
#include "utils/utils.h"

light::light(int id) :
    object(new lightHierarchyButton(*this, "images/icons/point_light.png", "Point light", id != 0)),
    id(id),
    lightTypeProp(dropdownProperty("Light type")),
    ambientColorProp(colorProperty("Ambient", ambientColor)),
    diffuseColorProp(colorProperty("Diffuse", diffuseColor)),
    specularColorProp(colorProperty("Specular", specularColor)),
    lightButton(dynamic_cast<lightHierarchyButton&>(*button)),
    spotConcentrationProp("Concentration", spotConcentration, 0.f, 30.f),
    spotlightCutOffProp("Cut Off", spotlightCutOff, 0.f, 100.f),
    constantAttProp("Constant Attenuation", constantAtt, 0.f, 1.f),
    linearAttProp("Linear Attenuation", linearAtt, 0.f, 1.f),
    quadraticAttProp("Quadratic Attenuation", quadraticAtt, 0.f, 0.2f),
    spotlightGroup("Spotlight Properties")
{
    canHaveMaterial = false;
    lightTypeProp.setElements({ "Point", "Directional", "Spot", "Ambient" });
    lightTypeProp.onClick = [&](int i) { setType(ofLightType(i)); };

    setScale({0.1f, 0.1f, 0.1f});

    setType(ofLightType::OF_LIGHT_POINT);
}

void light::customDraw()
{
    if (li.getType() == ofLightType::OF_LIGHT_AREA)
    {
        ofSetGlobalAmbientColor(ambientColor);
    }
    else
    {
        // dont forget to set position of orientation of ofLight
        li.setPosition(getPosition());
        li.setOrientation(getOrientationEuler());

        ofSetGlobalAmbientColor(ofColor(0, 0, 0));

        // also dont forget to set color
        li.setAmbientColor(ambientColor);
        li.setDiffuseColor(diffuseColor);
        li.setSpecularColor(specularColor);

        if (isSelected)
        {
            ofPushStyle();
            ofDisableLighting();
            ofNoFill();
            li.draw();
            ofEnableLighting();
            ofPopStyle();
        }
    }

    li.setAttenuation(constantAtt, linearAtt, quadraticAtt);
}

void light::drawProperties(int x, int y, int width, int originX, int originY)
{
    int offset = y;
    lightTypeProp.draw(x, offset, width);
    offset += 10 + lightTypeProp.getHeight();

    ambientColorProp.draw(x, offset, width);
    ambientColorProp.interactable = !lightTypeProp.focused;
    offset += 10 + ambientColorProp.getHeight();

    if (li.getType() != ofLightType::OF_LIGHT_AREA)
    {
        diffuseColorProp.draw(x, offset, width);
        diffuseColorProp.interactable = !lightTypeProp.focused;
        offset += 10 + diffuseColorProp.getHeight();

        specularColorProp.draw(x, offset, width);
        specularColorProp.interactable = !lightTypeProp.focused;
        offset += 10 + specularColorProp.getHeight();
    }

    constantAttProp.draw(x, offset, width);
    offset += 10 + constantAttProp.getHeight();

    linearAttProp.draw(x, offset, width);
    offset += 10 + linearAttProp.getHeight();

    quadraticAttProp.draw(x, offset, width);
    offset += 10 + quadraticAttProp.getHeight();

    if (li.getType() == ofLightType::OF_LIGHT_SPOT)
    {
        spotlightGroup.update(x, offset);
        spotlightGroup.setWidth(width);

        spotlightGroup.drawOnToggled = [&](int x, int y)
        {
            spotConcentrationProp.draw(x, y, width);
            spotlightCutOffProp.draw(x, y + 10 + spotConcentrationProp.getHeight(), width);
        };

        li.setSpotConcentration(spotConcentration);
        li.setSpotlightCutOff(spotlightCutOff);

        spotlightGroup.draw();
    }
}

void light::setType(ofLightType type)
{
    cout << "Set Light Type to: ";
    switch (type)
    {
    case ofLightType::OF_LIGHT_AREA:
        lightButton.setIcon("images/icons/area_light.png");
        lightButton.setLabel("Ambient");
        li.setAreaLight(0, 0);
        cout << "Ambient" << endl;
        break;

    case ofLightType::OF_LIGHT_DIRECTIONAL:
        li.setDirectional();
        lightButton.setIcon("images/icons/directional_light.png");
        lightButton.setLabel("Directional");
        cout << "Directional" << endl;
        break;

    case ofLightType::OF_LIGHT_POINT:
        li.setPointLight();
        lightButton.setIcon("images/icons/point_light.png");
        lightButton.setLabel("Point");
        cout << "Point" << endl;
        break;

    case ofLightType::OF_LIGHT_SPOT:
        li.setSpotlight();
        li.setSpotConcentration(2);
        li.setSpotlightCutOff(30);
        lightButton.setIcon("images/icons/spot_light.png");
        lightButton.setLabel("Spot");
        cout << "Spot" << endl;
        break;

    default:
        break;
    }
}
