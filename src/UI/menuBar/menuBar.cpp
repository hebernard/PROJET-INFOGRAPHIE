#include "menuBar.h"
#include "UI/dropdown/dropdown.h"
#include "dropdown/dropdownButton.h"
#include "menuBarButton.h"
#include "recButton.h"
#include "menuBarButtonAlt.h"
#include "components/2d/image.h"
#include "scene.h"
#include "components/2d/line.h"
#include "components/2d/circle.h"
#include "components/2d/ellipse.h"
#include "components/2d/rectangle.h"
#include "components/2d/square.h"
#include "components/2d/triangle.h"
#include "components/3d/bezierCurve.h"
#include "components/3d/sphere.h"
#include "components/3d/cube.h"
#include "components/3d/objectModel.h"
#include "panel.h"
#include "utils.h"

menuBar::menuBar() : ofxDatGuiComponent("menuBar"),
	rect(),
	logo(),
	dropdown2d(new dropdown(0, "2D", *this)),
	dropdown3d(new dropdown(1, "3D", *this)),
	raytracingDropdown(new dropdown(2, "3D", *this)),
	importButton(new menuBarButton("Import")),
	renderButton(new menuBarButton("Render")),
	themeButton(new menuBarButtonAlt(mainTheme::themePath()))
{
	rect.width = ofGetWidth();
	rect.height = 70;

	logo.load(mainTheme::logoPath());
	logo.resize(22, 22);

	//2D - Line Button
	dropdownButton* lineButton = new dropdownButton("images/icons/line.png", "Line");
	lineButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		line* li = new line(5);
		li->setPosition(glm::vec3(0, 1, 0));

		scene& s = s.getInstance();
		s.addObject(li);

		notifyDropdownClicked(-1);
	});
	dropdown2d->addButton(lineButton);

	//2D - Circle Button
	dropdownButton* circleButton = new dropdownButton("images/icons/circle.png", "Circle");
	circleButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		circle* circ = new circle(1.2f);

		scene& s = s.getInstance();
		s.addObject(circ);

		notifyDropdownClicked(-1);
	});
	dropdown2d->addButton(circleButton);

	//2D - Ellipse Button
	dropdownButton* ellipseButton = new dropdownButton("images/icons/ellipse.png", "Ellipse");
	ellipseButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		ellipse* elli = new ellipse(1.5f, 1.2f);

		scene& s = s.getInstance();
		s.addObject(elli);

		notifyDropdownClicked(-1);
	});
	dropdown2d->addButton(ellipseButton);

	//2D - Square Button
	dropdownButton* squareButton = new dropdownButton("images/icons/square.png", "Square");
	squareButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		square* sq = new square(1.2f);

		scene& s = s.getInstance();
		s.addObject(sq);

		notifyDropdownClicked(-1);
	});
	dropdown2d->addButton(squareButton);

	//2D - Rectangle Button
	dropdownButton* rectangleButton = new dropdownButton("images/icons/rectangle.png", "Rectangle");
	rectangleButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		rectangle* rect = new rectangle(1.5f, 1.0f);

		scene& s = s.getInstance();
		s.addObject(rect);

		notifyDropdownClicked(-1);
	});
	dropdown2d->addButton(rectangleButton);

	//2D - Triangle Button
	dropdownButton* triangleButton = new dropdownButton("images/icons/triangle.png", "Triangle");
	triangleButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		triangle* tri = new triangle(3, 2);

		scene& s = s.getInstance();
		s.addObject(tri);

		notifyDropdownClicked(-1);
	});
	dropdown2d->addButton(triangleButton);

	//3D - Curve Button
	dropdownButton* curveButton = new dropdownButton("images/icons/curve.png", "Curve");
	curveButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
		{
			bezierCurve* cu = new bezierCurve();

			scene& s = s.getInstance();
			s.addObject(cu);

			notifyDropdownClicked(-1);
		});
	dropdown3d->addButton(curveButton);

	//3D - Sphere Button
	dropdownButton* sphereButton = new dropdownButton("images/icons/sphere.png", "Sphere");
	sphereButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		sphere* sp = new sphere(1.2f);

		scene& s = s.getInstance();
		s.addObject(sp);

		notifyDropdownClicked(-1);
	});
	dropdown3d->addButton(sphereButton);

	//3D - Cube Button
	dropdownButton* cubeButton = new dropdownButton("images/icons/cube.png", "Cube");
	cubeButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		cube* cu = new cube(1.2f, 1.2f, 1.2f);

		scene& s = s.getInstance();
		s.addObject(cu);

		notifyDropdownClicked(-1);
	});
	dropdown3d->addButton(cubeButton);

	importButton->onButtonEvent(this, &menuBar::onImportButtonEvent);
	renderButton->buttonEventCallback = [&](auto e)
	{
		scene& s = s.getInstance();
		s.showRaytracingPanel = !s.showRaytracingPanel;
		if (s.showRaytracingPanel)
		{
			s.raytracing.setup();
			renderButton->setLabel(" Scene");
		}
		else
		{
			renderButton->setLabel("Render");
			s.raytracing.pause();
			if (s.currentSelected != nullptr)
			{
				s.currentSelected->propertiesOpened = false;
			}
		}
	};

	themeButton->onButtonEvent(this, &menuBar::onThemeButtonEvent);

	dropdownButton* r_sphereButton = new dropdownButton("images/icons/sphere.png", "Sphere");
	r_sphereButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		sphere* sp = new sphere(16.5f, { 45.f, 16.5f, 65.f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, 0);

		scene& s = s.getInstance();
		s.raytracing.addSphere(sp);

		notifyDropdownClicked(-1);
	});
	raytracingDropdown->addButton(r_sphereButton);
}

menuBar::~menuBar()
{
	delete dropdown2d;
	delete dropdown3d;
	delete raytracingDropdown;

	delete importButton;
	delete renderButton;
	delete themeButton;
}

void menuBar::draw()
{
	if (rect.inside(ofGetMouseX(), ofGetMouseY()))
	{
		utils::isMouseOverUI = true;
	}
	ofPushStyle();
	ofFill();

	ofSetColor(mainTheme::toolBarColor());
	ofDrawRectangle(rect);

	drawLogo();
	drawLine();

	scene& s = s.getInstance();
	if (!s.showRaytracingPanel)
	{
		dropdown2d->draw();
		dropdown3d->draw();
		importButton->draw(10);
	}
	else
	{
		raytracingDropdown->draw();
	}

	renderButton->draw(13);
	themeButton->draw();

	ofPopStyle();
}

void menuBar::update()
{
	rect.width = ofGetWidth();

	int posX = 180;
	int posY = rect.height / 2 - dropdown2d->getHeight() / 2;

	scene& s = s.getInstance();
	if (!s.showRaytracingPanel)
	{
		dropdown2d->setPosition(posX, posY);
		dropdown2d->update();
		posX += dropdown2d->getWidth() + 5;

		dropdown3d->setPosition(posX, posY);
		dropdown3d->update();
		posX += dropdown3d->getWidth() + 10;

		importButton->update(posX, posY + dropdown2d->getHeight() / 2 - importButton->getHeight() / 2);
		posX += importButton->getWidth() + 10;
	}
	else
	{
		raytracingDropdown->setPosition(posX, posY);
		raytracingDropdown->update();
		posX += raytracingDropdown->getWidth() + 10;
	}

	renderButton->update(posX, importButton->getY());
	themeButton->update(ofGetWidth() - (themeButton->getWidth()*2), posY + dropdown2d->getHeight() / 2 - themeButton->getHeight() / 2);
}

void menuBar::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void menuBar::notifyDropdownClicked(int index)
{
	// This is ugly but works for now
	if (index == 0)
	{
		dropdown3d->setChecked(false);
	}
	else if (index == 1)
	{
		dropdown2d->setChecked(false);
	}
	else if (index == -1)
	{
		dropdown2d->setChecked(false);
		dropdown3d->setChecked(false);
		raytracingDropdown->setChecked(false);
	}
}

void menuBar::drawLogo()
{
	ofSetColor(mainTheme::logoDownLayerColor());
	ofDrawRectRounded(20, rect.height / 2 - 15, 34, 34, 6);

	ofSetColor(mainTheme::logoTopLayerColor());
	ofDrawRectRounded(20, rect.height / 2 - 17, 34, 34, 6);

	ofSetColor(ofColor::white);
	logo.draw(26, rect.height / 2 - 9);
}

void menuBar::drawLine()
{
	ofSetLineWidth(2);
	ofSetColor(mainTheme::toolBarBorderColor());
	ofDrawLine(0, 71, ofGetWidth(), 71);
}

void menuBar::onImportButtonEvent(ofxDatGuiButtonEvent e)
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Choisir un objet à importer");

	scene& s = s.getInstance();

	if (openFileResult.bSuccess)
	{
		ofFile file(openFileResult.getPath());

		if (file.exists())
		{
			std::string fileExtension = ofToUpper(file.getExtension());

			if (fileExtension == "JPG" || fileExtension == "PNG")
			{
				s.addObject(new image(openFileResult.getPath()));
			}

			if (fileExtension == "OBJ" || fileExtension == "3DS" || fileExtension == "PLY" || fileExtension == "STL" || fileExtension == "DAE")
			{
				s.addObject(new objectModel(openFileResult.getPath()));
			}
		}
	}
}

void menuBar::onThemeButtonEvent(ofxDatGuiButtonEvent e)
{
	mainTheme::darkTheme = !mainTheme::darkTheme;
	ofSetBackgroundColor(mainTheme::sceneBackgroundColor());
	themeButton->updateIcon(mainTheme::themePath());
	logo.load(mainTheme::logoPath());
	logo.resize(22, 22);
}
