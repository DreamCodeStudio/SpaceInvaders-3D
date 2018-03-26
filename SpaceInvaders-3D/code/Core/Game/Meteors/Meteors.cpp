#include "Meteors.h"

void Meteors::Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship, irr::scene::IParticleAffector *particleAffector)
{
	//Save pointer to sceneManager, spaceship and particle affector
	_SceneManager = sceneManager;
	_Spaceship = spaceship;
	_ParticlePositionAffector = particleAffector; //Used to get the position of the particles and detect the collision of the laser beam with the meteors

	//Load mesh
	_MeteorMesh = _SceneManager->getMesh("Data\\Objects\\Meteor\\Meteor.obj");

	//Set seed to get random numbers
	srand(static_cast<unsigned int>(time(NULL)));

	//Create Particle System
	_ParticleSystem = _SceneManager->addParticleSystemSceneNode(false);
	_ParticleSystem->setMaterialTexture(0, _SceneManager->getVideoDriver()->getTexture("Data\\Textures\\Particle\\fireball.bmp"));
	_ParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

	_ParticleEmitter = nullptr;
	_ParticleDetractor = nullptr;

	//For the game over animation 
	_SpaceshipWasHitted = false;		//If the player has died -> if so go back to menu
}

int Meteors::Update()
{
	if (_SpawnClock.getElapsedTime().asMilliseconds() > sf::milliseconds(2000).asMilliseconds()) //Spawn a meteor after some time
	{
		_Meteors.push_back(_SceneManager->addAnimatedMeshSceneNode(_MeteorMesh, 0, -1, irr::core::vector3df(static_cast<float>((rand() % 44) - 22), static_cast<float>((rand() % 17) - 9), 150.0f))); //Create a meteor on a random position
		_SpawnClock.restart();
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(_TimeSinceLastFrame.getElapsedTime().asMilliseconds()); i++)
	{
		//Now update every Meteor so it flys to the player
		for (unsigned int c = 0; c < _Meteors.size(); c++)
		{
			_Meteors[c]->updateAbsolutePosition();
			_Meteors[c]->setPosition(irr::core::vector3df(_Meteors[c]->getAbsolutePosition().X, _Meteors[c]->getAbsolutePosition().Y, _Meteors[c]->getAbsolutePosition().Z - 0.01f));

			//Check if the Meteor is behind the player -> if so it can be deleted
			if (_Meteors[c]->getAbsolutePosition().Z < -50)
			{
				_Meteors[c]->remove();
				_Meteors.erase(_Meteors.begin() + c, _Meteors.begin() + c + 1);
			}
		}
	}
	_TimeSinceLastFrame.restart();

	//Check collison with spaceship
	this->CheckCollision();

	if (_SpaceshipWasHitted) //If the player died go back to menu
	{
		_SpaceshipWasHitted = false;
		return GAME_STATE_MENU;
	}

	return GAME_STATE_RUN;
}

void Meteors::Clear()
{
	//Clear all meteors and free memory
	for (unsigned int c = 0; c < _Meteors.size(); c++)
	{
		_Meteors[c]->remove();
	}
	_Meteors.clear();
}

/* ####### Private ######## */

void Meteors::CheckCollision()
{
	//Check collision with spaceship for every meteor
	for (unsigned int c = 0; c < _Meteors.size(); c++)
	{
		if (_Meteors[c]->getTransformedBoundingBox().intersectsWithBox(_Spaceship->getTransformedBoundingBox())) //If the spaceship box intersect with the meteor box -> there is a collision
		{
			_SpaceshipWasHitted = true;
			return;
		}
	}

	//Check collision with the laser beam
	for (unsigned int c = 0; c < static_cast<ParticlePositionAffector*>(_ParticlePositionAffector)->GetParticlePositions()->size(); c++) //Check all particles 
	{
		for (unsigned int i = 0; i < _Meteors.size(); i++)		//Check all Meteors
		{
			if (_Meteors[i]->getTransformedBoundingBox().isPointInside(static_cast<ParticlePositionAffector*>(_ParticlePositionAffector)->GetParticlePositions()->at(c))) //If the particle is inside the meteor -> collision detected
			{		
				//KNOWN BUG: If the game runs with less fps the collision detection does not work always correctly
				// If the ParticleDetractor or Emitter was already created drop it first
				if (_ParticleDetractor != nullptr)  
				{
					_ParticleDetractor->drop();
				}
				if (_ParticleEmitter != nullptr)
				{
					_ParticleEmitter->drop();
				}

				//Remove all previouse added affectors
				_ParticleSystem->removeAllAffectors();

				//Create the boxemiiter for the meteor which was destroyed
				_ParticleEmitter = _ParticleSystem->createBoxEmitter(_Meteors[i]->getTransformedBoundingBox(), irr::core::vector3df(0, 0, 0), 500, 500, irr::video::SColor(255, 255, 255, 255), 
																																						irr::video::SColor(255, 255, 255, 255), 1000, 1000, 0, irr::core::dimension2df(0.5f, 0.5f),
																																																			   irr::core::dimension2df(1.0f, 1.0f));
				//Set Emitter for the Particle System
				_ParticleSystem->setEmitter(_ParticleEmitter);
			
				//Create and add particle affector so the particles fly away from the meteor so it looks like a nice explosion
				_ParticleDetractor = _ParticleSystem->createAttractionAffector(irr::core::vector3df(_Meteors[i]->getAbsolutePosition().X, _Meteors[i]->getAbsolutePosition().Y, _Meteors[i]->getAbsolutePosition().Z - 1.0f), 25.0f, false);
				_ParticleSystem->addAffector(_ParticleDetractor);

				//Start Explosion clock (after 50 ms no more particles are spawned)
				_ExplosionClock.restart();

				//Remove Meteor from list
				_Meteors[i]->remove();
				_Meteors.erase(_Meteors.begin() + i, _Meteors.begin() + i + 1);
				i = 0;
				c = 0;
			}
		}
	}

	//Do not spawn any new particles after 50 ms 
	if (_ExplosionClock.getElapsedTime().asMilliseconds() > sf::milliseconds(50).asMilliseconds() && _ParticleEmitter != nullptr) //After some milliseconds no new particle should appear
	{	
		_ParticleEmitter->setMaxParticlesPerSecond(0);
	}
}