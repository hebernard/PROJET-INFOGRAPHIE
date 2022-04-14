#include "bezierSurface.h"
#include "camera.h"
#include "scene.h"
#include "utils/utils.h"

//-------------------------------------------------------------=
//-------------------  Bezier Surface -------------------------=
//-------------------------------------------------------------=

bezierSurface::bezierSurface() 
	: object(new hierarchyButton(*this, "images/icons/surface.png", "Surface")),
    surfaceVisibilityCheckbox("Surface", drawSurface),
    surfaceWidthSlider("Width", surfaceWidth, minDimension - 1, maxDimension, true),
    surfaceHeightSlider("Height", surfaceHeight, minDimension - 1, maxDimension, true),
    surfaceColorProperty("Surface Color", surfaceColor),
    outlineColorProperty("Outline Color", outlineColor),
    outlineVisibilityCheckbox("Control Points", drawOutline),
    ctrlPointsRadiusInput("Control Points Size", controlPointsRadius),
    selectedPointsSlider("Selected", false), 
    resetButton("Reset", 10),
    randomButton("Random", 12)
{
    //canHaveMaterial = false;

    //---  Setup Control Points Vectors  -------------------------

    for (int i = 0; i <= surfaceDimension; i++) {
        inputs.push_back(vector<ofVec3f>());
        for (int j = 0; j <= surfaceDimension; j++) {
            inputs[i].push_back(ofVec3f());
        }
    }
    for (int i = 0; i < surfaceResolution; i++) {
        outputs.push_back(vector<ofVec3f>());
        for (int j = 0; j < surfaceResolution; j++) {
            outputs[i].push_back(ofVec3f());
        }
    }

    //---  Setup Surface  ----------------------------------------

    surface = ofMesh::plane(surfaceWidth, surfaceHeight, surfaceResolution, surfaceResolution, OF_PRIMITIVE_TRIANGLES);
    reset();

    vector<glm::vec3> verts = surface.getVertices();
    for (int i = 0; i < verts.size(); i++) {
        surface.setTexCoord(i, ofVec2f(verts[i].x, verts[i].y));
    }

    //---  Setup Properties  ------------------------------------

    surfaceWidthSlider.onUpdate = [&](float value) {
        surfaceWidth = value;
        resetSurface();
    };

    surfaceHeightSlider.onUpdate = [&](float value) {
        surfaceHeight = value;
        resetSurface();
    };

    selectedPointsSlider.onUpdate = [&](auto axis, float value) {
        trans = axis * value;

        for (int i = 0; i < selectedPoints.size(); i++) {
            inputs[selectedPoints[i].x][selectedPoints[i].y] += trans * ofGetLastFrameTime();
        }
        createSurface();
    };
    

    selectedPointsSlider.resetButton->buttonEventCallback = [&](auto e) {
        //reset();
        selectedPoints.clear();
    };

    resetButton.onClick = [&]() {
        reset();
    };

    randomButton.onClick = [&]() {
        random();
    };

}

bezierSurface::~bezierSurface()
{
    surface.clear();
    inputs.clear();
    outputs.clear();
    selectedPoints.clear();
}

void bezierSurface::customDraw()
{
    if (isSelected) {
        ofDisableDepthTest();
    }

    //---  Update Surface  --------------------------------

    if (utils::mousePressed && !utils::isMouseOverUI && isSelected) {
        findPoint(ofGetMouseX(), ofGetMouseY());
    }
    if (utils::keyPressed == OF_KEY_UP && isSelected && surfaceResolution < maxDimension) {
        surfaceResolution++;
        resetSurface();
    }
    if (utils::keyPressed == OF_KEY_DOWN && isSelected && surfaceResolution > minDimension) {
        surfaceResolution--;
        resetSurface();
    }

    //---  Draw Surface  --------------------------------------

    if (drawSurface) {
        ofSetColor(surfaceColor);
        surface.draw();
    }
    else {
        ofSetColor(outlineColor);
        surface.drawWireframe();
    }

    material->end();

    //---  Draw Controls  -------------------------------------

    if (isSelected && drawOutline) {
        drawOutlines();
    }

    if (isSelected) {
        ofEnableDepthTest();
    }
}

void bezierSurface::drawOutlines()
{
    for (int i = 0; i <= surfaceDimension; i++) {
        for (int j = 0; j <= surfaceDimension; j++) {

            for (int k = 0; k < selectedPoints.size(); k++) {
                if (selectedPoints[k].x == i && selectedPoints[k].y == j) {
                    ofSetColor(selectedColor);
                    break;
                }
                else
                    ofSetColor(outlineColor);
            }

            ofPoint tmpInput(inputs[i][j]);
            ofPoint tmpOutput(outputs[i][j]);

            ofDrawSphere(tmpInput, controlPointsRadius);

            ofSetColor(controlPointsColor);
            ofDrawSphere(tmpOutput, controlPointsRadius / 2);

            ofSetColor(outlineColor);
            ofSetLineWidth(controlPointsRadius);
            ofDrawLine(tmpInput, tmpOutput);

        }
    }
}

void bezierSurface::drawProperties(int x, int y, int width, int originX, int originY)
{
    int offset = y;
    surfaceVisibilityCheckbox.draw(x, offset, width);
    offset += 10 + surfaceVisibilityCheckbox.getHeight();
    surfaceWidthSlider.draw(x, offset, width);
    offset += 10 + surfaceWidthSlider.getHeight();
    surfaceHeightSlider.draw(x, offset, width);
    offset += 10 + surfaceHeightSlider.getHeight();
    surfaceColorProperty.draw(x, offset, width);

    offset += 10 + surfaceColorProperty.getHeight();
    outlineColorProperty.draw(x, offset, width);
    offset += 10 + outlineColorProperty.getHeight();
    outlineVisibilityCheckbox.draw(x, offset, width);


    offset += 10 + outlineVisibilityCheckbox.getHeight();
    ctrlPointsRadiusInput.draw(x, offset, width);

    selectedPointsSlider.update();
    offset += 20 + ctrlPointsRadiusInput.getHeight();
    selectedPointsSlider.draw(x, offset, width, trans);

    offset += 20 + selectedPointsSlider.getHeight();
    resetButton.setWidth(width);
    resetButton.update(x, offset, originX, originY);
    resetButton.draw();
    offset += 20 + resetButton.getHeight();
    randomButton.setWidth(width);
    randomButton.update(x, offset, originX, originY);
    randomButton.draw();

}

void bezierSurface::reset()
{
    //---  Setup Control Points  ---------------------------------

    for (int i = 0; i <= surfaceDimension; i++) {
        for (int j = 0; j <= surfaceDimension; j++) {
            inputs[i][j].x = ofMap(i, 0, surfaceDimension, 0, surfaceWidth);
            inputs[i][j].y = ofMap(j, 0, surfaceDimension, 0, surfaceHeight);
            inputs[i][j].z = 0;
        }
    }

    createSurface();
}

void bezierSurface::random()
{
    //---  Random Control Points  ---------------------------------

    for (int i = 0; i <= surfaceDimension; i++) {
        for (int j = 0; j <= surfaceDimension; j++) {
            inputs[i][j].x = ofMap(i, 0, surfaceDimension, 0, surfaceWidth);
            inputs[i][j].y = ofMap(j, 0, surfaceDimension, 0, surfaceHeight);
            float rand = ofRandom(-1, 1);
            if (rand > 0) {
                inputs[i][j].z = ofRandom(0, surfaceHeight / 2);
            }
            else {
                inputs[i][j].z = 0;
            }

        }
    }

    createSurface();
}

void bezierSurface::resetSurface()
{
    inputs.clear();
    outputs.clear();
    surface.clear();

    surfaceDimension = surfaceResolution - 1;

    //---  Setup Control Points Vectors  -------------------------

    for (int i = 0; i <= surfaceDimension; i++) {
        inputs.push_back(vector<ofVec3f>());
        for (int j = 0; j <= surfaceDimension; j++) {
            inputs[i].push_back(ofVec3f());
        }
    }
    for (int i = 0; i < surfaceResolution; i++) {
        outputs.push_back(vector<ofVec3f>());
        for (int j = 0; j < surfaceResolution; j++) {
            outputs[i].push_back(ofVec3f());
        }
    }

    //---  Setup Surface  ----------------------------------------

    surface = ofMesh::plane(surfaceWidth, surfaceHeight, surfaceResolution, surfaceResolution, OF_PRIMITIVE_TRIANGLES);
    reset();

    vector<glm::vec3> verts = surface.getVertices();
    for (int i = 0; i < verts.size(); i++) {
        surface.setTexCoord(i, ofVec2f(verts[i].x, verts[i].y));
    }
}

void bezierSurface::findPoint(int mouseX, int mouseY)
{
    ofPoint point;
    ofPoint screenPoint = ofVec3f(mouseX, mouseY, 0);
    ofPoint worldPoint;
    //worldPoint = c->screenToWorld(screenPoint);
    //distance = ofDist(inputs[i][j].x, inputs[i][j].y, mouseX, mouseY);

    float distance = 0;
    float nearest = -1;

    scene& s = s.getInstance();
    std::vector<camera*> cams = s.getCameras();


    for (auto& c : cams) {
        for (int i = 0; i <= surfaceDimension; i++) {
            for (int j = 0; j <= surfaceDimension; j++) {

                worldPoint = c->worldToScreen(inputs[i][j]);

                //cout << "Screen : " << screenPoint << endl;
                //cout << "World : " << worldPoint << endl;

                distance = ofDist(worldPoint.x, worldPoint.y, screenPoint.x, screenPoint.y);
                //cout << "Distance :" + ofToString(distance) << endl;

                if (nearest == -1)
                    nearest = distance;
                if (distance < 20 && distance < nearest) {
                    point.set(i, j);
                    nearest = distance;
                }

            }
        }
    }


    bool isMissing = true;
    for (int i = 0; i < selectedPoints.size(); i++) {
        if (selectedPoints[i].x == point.x && selectedPoints[i].y == point.y)
            isMissing = false;
    }

    if (isMissing)
        selectedPoints.push_back(point);
}

//==============================================================
//---  Bezier Equations ----------------------------------------
//==============================================================

void bezierSurface::createSurface()
{
    outputs = calculateSurface(inputs, outputs, surfaceDimension, surfaceDimension, surfaceResolution, surfaceResolution);

    vector<ofVec3f> verts;
    for (int i = 0; i < surfaceResolution; i++) {
        for (int j = 0; j < surfaceResolution; j++) {
            verts.push_back(outputs[i][j]);
        }
    }
    for (int i = 0; i < verts.size(); i++) {
        surface.setVertex(i, verts[i]);
    }
}

vector<vector<ofVec3f>> bezierSurface::calculateSurface(vector<vector<ofVec3f>> inp, vector<vector<ofVec3f>> outp, int dimensionx, int dimensiony, int resolutionx, int resolutiony)
{
    // From http://paulbourke.net/geometry/bezier/

    double mui, muj;
    double bi, bj;

    //---  Calculate Bezier Surface  ---------------------------------

    for (int i = 0; i < resolutionx; i++) {
        mui = i / (double)(resolutionx - 1);
        for (int j = 0; j < resolutiony; j++) {
            muj = j / (double)(resolutiony - 1);

            outp[i][j].x = 0;
            outp[i][j].y = 0;
            outp[i][j].z = 0;

            for (int ki = 0; ki <= dimensionx; ki++) {
                bi = bezierBlend(ki, mui, dimensionx);
                for (int kj = 0; kj <= dimensiony; kj++) {
                    bj = bezierBlend(kj, muj, dimensiony);
                    outp[i][j].x += (inp[ki][kj].x * bi * bj);
                    outp[i][j].y += (inp[ki][kj].y * bi * bj);
                    outp[i][j].z += (inp[ki][kj].z * bi * bj);
                }
            }
        }
    }

    return outp;
}

double bezierSurface::bezierBlend(int k, double mu, int n)
{
    // From http://paulbourke.net/geometry/bezier/

    int nn, kn, nkn;
    double blend = 1;

    nn = n;
    kn = k;
    nkn = n - k;

    while (nn >= 1) {
        blend *= nn;
        nn--;
        if (kn > 1) {
            blend /= (double)kn;
            kn--;
        }
        if (nkn > 1) {
            blend /= (double)nkn;
            nkn--;
        }
    }
    if (k > 0)
        blend *= pow(mu, (double)k);
    if (n - k > 0)
        blend *= pow(1 - mu, (double)(n - k));

    return(blend);
}

