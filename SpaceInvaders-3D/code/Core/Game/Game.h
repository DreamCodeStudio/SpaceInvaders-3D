#pragma once
#include <irrlicht.h>
#include <SFML\Graphics.hpp>

#include <iostream>

#include "..\Defines.h"

class Game
{
	public:

		enum MOVEMENT {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		void Create(irr::scene::ISceneManager *sceneManager);

		int Update();
		void Render();

	private:

		void CheckUserInput();

		irr::scene::ISceneManager *_SceneManager;

		irr::scene::ICameraSceneNode *_GameCamera;
		
		// 3D-Game objects 
		irr::scene::IAnimatedMeshSceneNode *_Spaceship;

		//Time measure
		sf::Clock _HorizontalTimer, _VerticalTimer;

		MOVEMENT _VerticalMovement, _HorizontalMovement;
};