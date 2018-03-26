#include "EnemyHandler.h"

void EnemyHandler::Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship, irr::scene::IParticleAffector *particleAffector)
{
	//Save pointer to parameter
	_SceneManager = sceneManager;
	_Spaceship = spaceship;
	_ParticleAffector = particleAffector;
	_SceneManager->getMesh("Data\\Objects\\EnemySpaceship\\EnemySpaceship.obj"); //Load the mesh for the enemy spaceship so irrlicht keeps it loaded into a buffer and does not stutter for some milliseconds when the first enemy spawns.
}

int EnemyHandler::Update()
{
	//Update all enemys
	for (unsigned int c = 0; c < _Enemys.size(); c++)
	{
		if (_Enemys[c]->Update() == GAME_STATE_MENU)	//Update all Enemys. If an enemy crashed into the player -> the player died go back to menu
		{
			return GAME_STATE_MENU;
		}

		if (!_Enemys[c]->IsAlive())		//If enemy died -> remove from vector
		{
			delete _Enemys[c];			//Free memory
			_Enemys.erase(_Enemys.begin() + c, _Enemys.begin() + c + 1); //Remove from vector
			return GAME_STATE_RUN;
		}
	}

	//Spawn a new enemy every 5 seconds
	if (_SpawnClock.getElapsedTime().asMilliseconds() > sf::milliseconds(3000).asMilliseconds())
	{
		_Enemys.push_back(new Enemy);	//Create enemy object
		_Enemys[_Enemys.size() - 1]->Create(_SceneManager, _Spaceship, _ParticleAffector);	 //Create it
		_SpawnClock.restart();		//Restart spawn clock
	}

	return GAME_STATE_RUN;
}

void EnemyHandler::Clear()
{
	//Free the whole memory for all enemys
	for (unsigned int c = 0; c < _Enemys.size(); c++)
	{
		_Enemys[c]->Clear(); //Remove scene node
		delete _Enemys[c];	//Free memory
	}
	_Enemys.clear();		//Clear the vector
}