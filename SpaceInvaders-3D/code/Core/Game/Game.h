#pragma once
#include <irrlicht.h>
#include <SFML\Graphics.hpp>

#include <iostream>
#include <thread>

#include "..\Defines.h"
#include "..\..\ParticlePositionAffector\ParticlePositionAffector.h"
#include "Meteors\Meteors.h"
#include "EnemyHandler\EnemyHandler.h"
#include "ScoreCounter\ScoreCounter.h"

class Game
{
	public:

		void Create(irr::IrrlichtDevice *device, irr::scene::ISceneManager *sceneManager);

		int Update();
		void Render();

	private:

		void CheckMovementInput();
		void CheckFireInput();
		void GameOverAnimation();

		irr::IrrlichtDevice *_Device;
		irr::scene::ISceneManager *_SceneManager;

		irr::scene::ICameraSceneNode *_GameCamera;
		
		// 3D-Game objects 
		irr::scene::IAnimatedMeshSceneNode *_Spaceship;

		//Time measure
		sf::Clock _HorizontalTimer, _VerticalTimer, _TimeSinceLastFrame;
		sf::Clock _LaserTimer, _FireCooldown;

		//Particle engine for laser 
		irr::scene::IParticleSystemSceneNode *_ParticleSystem;
		irr::scene::IParticleBoxEmitter *_BoxEmitter;
		irr::scene::IParticleAffector *_ParticleAffector;

		//Prelaser so the player can see where he is shooting at
		irr::scene::IAnimatedMeshSceneNode *_Prelaser;

		//Meteors 
		Meteors _Meteors;

		//Enemy
		EnemyHandler _EnemyHandler;

		//ScoreCounter
		ScoreCounter _ScoreCounter;

		//Game over animation
		bool _PlayerIsAlive, _GameOverAnimationFinished;
};