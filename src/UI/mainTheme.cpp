#include "mainTheme.h"

bool mainTheme::darkTheme = true;

const std::string mainTheme::fontRegularPath = "fonts/inter_regular.ttf";
const std::string mainTheme::fontMediumPath = "fonts/inter_medium.ttf";
std::string mainTheme::logoPath() { return darkTheme ? "images/logoDark.png" : "images/logoLight.png"; }
std::string mainTheme::themePath() { return darkTheme ? "images/icons/moon.png" : "images/icons/sun.png"; }

ofColor mainTheme::fontColor() { return darkTheme ? ofColor(245) : ofColor(46); }
ofColor mainTheme::fontColorAlpha() { return darkTheme ? ofColor(245, 128) : ofColor(46, 128); }

ofColor mainTheme::logoTopLayerColor() { return darkTheme ? ofColor(70) : ofColor(217); }
ofColor mainTheme::logoDownLayerColor() { return darkTheme ? ofColor(36) : ofColor(196); }

ofColor mainTheme::toolBarColor() { return darkTheme ? ofColor(18) : ofColor(237); }
ofColor mainTheme::toolBarBorderColor() { return darkTheme ? ofColor(53) : ofColor(178); }
ofColor mainTheme::toolBarButtonHoverColor() { return darkTheme ? ofColor(35) : ofColor(219); }

ofColor mainTheme::panelColor() { return darkTheme ? ofColor(49) : ofColor(232); }
ofColor mainTheme::panelBorderColor() { return darkTheme ? ofColor(59) : ofColor(212); }
ofColor mainTheme::panelButtonHoverColor() { return darkTheme ? ofColor(100) : ofColor(195); }

ofColor mainTheme::color1() { return darkTheme ? ofColor(87, 140, 245) : ofColor(86, 138, 242); }
ofColor mainTheme::color2() { return darkTheme ? ofColor(115, 157, 247) : ofColor(91, 146, 255); }
ofColor mainTheme::color3() { return darkTheme ? ofColor(58, 119, 243) : ofColor(81, 131, 229); }

ofColor mainTheme::sceneBackgroundColor() { return darkTheme ? ofColor(36) : ofColor(128); }
ofColor mainTheme::gridColor1() { return darkTheme ? ofColor(50, 120) : ofColor(100, 120); }
ofColor mainTheme::gridColor2() { return darkTheme ? ofColor(150) : ofColor(200); }