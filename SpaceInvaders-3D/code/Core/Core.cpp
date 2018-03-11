#include "Core.h"

Core::Core()
{
	// Create window and get scenemanager, and video driver 
	_Device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, true, 0);
	_Driver = _Device->getVideoDriver();
	_SceneManager = _Device->getSceneManager();

	//Create game
	_Game.Create(_Device, _SceneManager);

	//Create Main menu
	_Menu.Create(_SceneManager);
}

void Core::Run()
{
	sf::Clock frameLimiter;

	while (_Device->run())
	{
		frameLimiter.restart();
		_Driver->beginScene(true, true, irr::video::SColor(50, 50, 50, 50));

		_SceneManager->drawAll();

		this->Update();
		this->Render();

		_Driver->endScene();

	//	while (frameLimiter.getElapsedTime().asMilliseconds() < sf::milliseconds(100).asMilliseconds());
	//	std::cout << "FPS: " <<  1000.0f / frameLimiter.getElapsedTime().asMilliseconds() << std::endl;
	}
}

/* ########## Private ########### */

void Core::Update()
{
	switch (_GameState)
	{
		case GAME_STATE_MENU: {
			_GameState = _Menu.Update();
		}
	    break;
		case GAME_STATE_RUN: {
			_GameState = _Game.Update();
		}
	}
}

void Core::Render()
{
	switch (_GameState)
	{
		case GAME_STATE_MENU: {
			_Menu.Render();
		}
		break;
		case GAME_STATE_RUN: {
			 _Game.Render();
		}
	}
}