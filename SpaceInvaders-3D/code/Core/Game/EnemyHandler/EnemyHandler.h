#pragma once
#include <iostream>
#include <irrlicht.h>
#include <SFML\Graphics.hpp>

#include "Enemy\Enemy.h"

class EnemyHandler
{
	public:

		void Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship, irr::scene::IParticleAffector *particleAffector);

		int Update();
		void Clear();

	private:

		irr::scene::ISceneManager *_SceneManager;
		irr::scene::IAnimatedMeshSceneNode *_Spaceship;
		irr::scene::IParticleAffector *_ParticleAffector;

		std::vector<Enemy*> _Enemys;

		sf::Clock _SpawnClock;

};