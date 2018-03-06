#include "Menu.h"

void Menu::Create(irr::scene::ISceneManager *sceneManager)
{
	//Save pointer to sceneManager
	_SceneManager = sceneManager;

	//Create camera for the menu
	irr::scene::ISceneNodeAnimator *animator = _SceneManager->createFlyCircleAnimator(irr::core::vector3df(0, 0, 0), 500, 0.00005f);
	_MenuCamera = _SceneManager->addCameraSceneNode();
	_MenuCamera->addAnimator(animator);

	_GUI = _SceneManager->getGUIEnvironment();
	irr::gui::IGUIFont *font = _GUI->getFont("Data\\Font\\rpgfont.xml");
	_GUI->getSkin()->setFont(font);

	// Create Play Button 
	_PlayButton = _GUI->addButton(irr::core::rect<irr::s32>(50, 50, 200, 90), 0, -1, irr::core::stringw("Play").c_str(), 0);

	// Load skydome (the skydome scene node is added to the scene manager and will still be visible even if the game state changes to GAME_STATE_RUN) 
	irr::scene::ISceneNode *skydome = _SceneManager->addSkyDomeSceneNode(_SceneManager->getVideoDriver()->getTexture("Data\\Textures\\World\\Skydome.jpg"));
}

int Menu::Update()
{
	_SceneManager->setActiveCamera(_MenuCamera); //Set Menu camera as active if the user just went from GAME_STATE_RUN to GAME_STATE_MENU

	/* Check if the user is pressing a button */
	if (_PlayButton->isPressed())
	{
		return GAME_STATE_RUN;
	}

	return GAME_STATE_MENU;
}

void Menu::Render()
{
	_GUI->drawAll();
}