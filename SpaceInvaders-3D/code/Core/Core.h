#pragma once
#include <irrlicht.h>

#include "Defines.h"

//Include game states 
#include "Game\Game.h"
#include "Menu\Menu.h"

class Core
{
	public:

		Core();

		void Run();

	private:

		void Update();
		void Render();

		irr::IrrlichtDevice *_Device;
		irr::video::IVideoDriver *_Driver;
		irr::scene::ISceneManager *_SceneManager;

		int _GameState;

		//Object for each game state
		Game _Game;
		Menu _Menu;

};