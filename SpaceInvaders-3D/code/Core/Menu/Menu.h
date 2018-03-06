#pragma once
#include <irrlicht.h>

#include "..\Defines.h"

class Menu
{
	public:

		void Create(irr::scene::ISceneManager *sceneManager);

		int Update();
		void Render();

	private:

		irr::scene::ISceneManager *_SceneManager;

		irr::scene::ICameraSceneNode *_MenuCamera;

		//GUI
		irr::gui::IGUIEnvironment *_GUI;
		irr::gui::IGUIButton *_PlayButton;
};