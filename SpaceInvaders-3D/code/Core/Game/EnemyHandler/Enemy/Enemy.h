#pragma once
#include <irrlicht.h>
#include <SFML\Graphics.hpp>
#include <iostream>

#include <ctime>

#include "..\..\..\Defines.h"
#include "..\..\ParticlePositionAffector\ParticlePositionAffector.h"

class Enemy
{
	public:

		void Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship, irr::scene::IParticleAffector *particleAffector);

		int Update();
		void Clear();

		bool IsAlive();

	private:

		void CheckCollision();
		void Move();

		irr::scene::ISceneManager *_SceneManager;
		irr::scene::IAnimatedMeshSceneNode *_Spaceship;
		
		irr::scene::IParticleAffector *_ParticleAffector;
		irr::scene::IParticleAffector *_ParticleDetractor;
		irr::scene::IParticleSystemSceneNode *_ParticleSystem;
		irr::scene::IParticleEmitter *_ParticleEmitter;
		sf::Clock _ExplosionClock;

		irr::scene::IAnimatedMeshSceneNode *_EnemyShip;

		sf::Clock _TimeSinceLastFrame;

		int _VerticalMovement, _HorizontalMovement;

		bool _Alive;
		bool _SpaceshipWasHitted;
		
};