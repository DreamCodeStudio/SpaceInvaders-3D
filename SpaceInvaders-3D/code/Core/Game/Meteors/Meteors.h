#pragma once
#include <irrlicht.h>
#include <SFML\Graphics.hpp>

#include <iostream>
#include <ctime>

#include "..\..\ParticlePositionAffector\ParticlePositionAffector.h"
#include "..\..\Defines.h"

class Meteors
{
	public:

		void Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship, irr::scene::IParticleAffector *particleAffector);

		int Update();
		void Clear();

	private:

		void CheckCollision();

		irr::scene::ISceneManager *_SceneManager;
		irr::scene::IAnimatedMeshSceneNode *_Spaceship;
		irr::scene::IParticleAffector *_ParticlePositionAffector;

		//Spawn a meteor after some time
		sf::Clock _SpawnClock;
		sf::Clock _TimeSinceLastFrame;

		//List for the meteors
		std::vector<irr::scene::IAnimatedMeshSceneNode*> _Meteors;
		irr::scene::IAnimatedMesh *_MeteorMesh;

		//Particle system for explosion
		irr::scene::IParticleSystemSceneNode *_ParticleSystem;
		irr::scene::IParticleBoxEmitter *_ParticleEmitter;
		irr::scene::IParticleAffector *_ParticleDetractor;
		sf::Clock _ExplosionClock;

		bool _SpaceshipWasHitted;

};