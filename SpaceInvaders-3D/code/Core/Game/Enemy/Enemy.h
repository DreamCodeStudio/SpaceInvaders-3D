#pragma once
#include <irrlicht.h>
#include <SFML\Graphics.hpp>
#include <iostream>

#include <ctime>

#include "..\..\Defines.h"

class Enemy
{
	public:

		void Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship);

		void Update();

	private:

		irr::scene::ISceneManager *_SceneManager;
		irr::scene::IAnimatedMeshSceneNode *_Spaceship;

		irr::scene::IAnimatedMeshSceneNode *_EnemyShip;

		sf::Clock _TimeSinceLastFrame;

		int _VerticalMovement, _HorizontalMovement;
		
};