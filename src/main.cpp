#include "ofMain.h"
#include "ofApp.h"

int main()
{
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 3);
    settings.setSize(1280, 720);
    settings.numSamples = 4;
    settings.doubleBuffering = true;
    ofCreateWindow(settings);

    ofRunApp(new ofApp());
}
