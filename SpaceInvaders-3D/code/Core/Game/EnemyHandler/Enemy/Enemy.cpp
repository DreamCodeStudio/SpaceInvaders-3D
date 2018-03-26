#include "Enemy.h"

void Enemy::Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship, irr::scene::IParticleAffector *particleAffector)
{
	//Seed for random number generation
	srand(static_cast<unsigned int>(time(NULL)));

	//Save pointer to parameter
	_SceneManager = sceneManager;
	_Spaceship = spaceship;
	_ParticleAffector = particleAffector;

	//Create Enemy spaceship
	_EnemyShip = _SceneManager->addAnimatedMeshSceneNode(_SceneManager->getMesh("Data\\Objects\\EnemySpaceship\\EnemySpaceship.obj"), 0, -1, irr::core::vector3df(static_cast<float>((rand() % 44) - 22), /*static_cast<float>((rand() % 17) - 9)*/ 9, 100.0f)); 

	//Set random direction at start
	_VerticalMovement = rand() % 2;
	_HorizontalMovement = rand() % 2 + 2;

	//Create Particle System for explosion
	_ParticleSystem = _SceneManager->addParticleSystemSceneNode(false);
	_ParticleSystem->setMaterialTexture(0, _SceneManager->getVideoDriver()->getTexture("Data\\Textures\\Particle\\fireball.bmp"));
	_ParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

	_ParticleEmitter = nullptr;
	_ParticleDetractor = nullptr;

	_Alive = true; //Enemy is alive at the beginning
	_SpaceshipWasHitted = false; //Player is alive at the start
}

int Enemy::Update()
{
	this->Move();
	this->CheckCollision();

	if (_SpaceshipWasHitted) //If the player died go back to menu
	{
		return GAME_STATE_MENU;
	}

	return GAME_STATE_RUN;
}

bool Enemy::IsAlive()
{
	return _Alive;		//Give back if the enemy is still alive -> if not it will be deleted from the enemy handler
}

void Enemy::Clear()
{
	_EnemyShip->remove(); //Remove enemy scene node
}

/* ##### Private ##### */

void Enemy::Move()
{
	//Move enemy to the player
	for (unsigned int c = 0; c < static_cast<unsigned int>(_TimeSinceLastFrame.getElapsedTime().asMilliseconds()); c++)
	{
		_EnemyShip->updateAbsolutePosition();
		_EnemyShip->setPosition(irr::core::vector3df(_EnemyShip->getAbsolutePosition().X - _EnemyShip->getRotation().Z * 0.0005f, _EnemyShip->getAbsolutePosition().Y + _EnemyShip->getRotation().X * 0.0005f, _EnemyShip->getAbsolutePosition().Z - 0.01f));

		//If the spaceship reaches the top or bot border of the screen change it's vertical movement
		if (_EnemyShip->getAbsolutePosition().Y > 8.0f)
		{
			_VerticalMovement = DOWN;
			_HorizontalMovement = rand() % 2 + 2;  //Random new horizontal movement
		}
		if (_EnemyShip->getAbsolutePosition().Y < -9.0f)
		{
			_VerticalMovement = UP;
			_HorizontalMovement = rand() % 2 + 2;  //Random new horizontal movement
		}

		//If the spaceship reaches the left or right border of the screen change it's horizontal movement
		if (_EnemyShip->getAbsolutePosition().X < -22.0f)
		{
			_HorizontalMovement = RIGHT;
			_VerticalMovement = rand() % 2;  //Random new vertical movment
		}
		if (_EnemyShip->getAbsolutePosition().X > 22.0f)
		{
			_HorizontalMovement = LEFT;
			_VerticalMovement = rand() % 2;  //Random new vertical movment
		}

		//Rotate spaceship up/down/
		switch (_VerticalMovement)
		{
			case UP: {
				if (_EnemyShip->getRotation().X < 20)
				{
					_EnemyShip->setRotation(irr::core::vector3df(_EnemyShip->getRotation().X + 0.045f, _EnemyShip->getRotation().Y, _EnemyShip->getRotation().Z));
				}
			}
					 break;
			case DOWN: {

				if (_EnemyShip->getRotation().X > -20)
				{
					_EnemyShip->setRotation(irr::core::vector3df(_EnemyShip->getRotation().X - 0.045f, _EnemyShip->getRotation().Y, _EnemyShip->getRotation().Z));
				}
			}
				   break;
		}
		//Rotatae spaceship left/right/
		switch (_HorizontalMovement)
		{
			case LEFT: {
				if (_EnemyShip->getRotation().Z < 20)
				{
					_EnemyShip->setRotation(irr::core::vector3df(_EnemyShip->getRotation().X, _EnemyShip->getRotation().Y, _EnemyShip->getRotation().Z + 0.045f));
				}

			}
					   break;
			case RIGHT: {
				if (_EnemyShip->getRotation().Z > -20)
				{
					_EnemyShip->setRotation(irr::core::vector3df(_EnemyShip->getRotation().X, _EnemyShip->getRotation().Y, _EnemyShip->getRotation().Z - 0.045f));
				}

			}
						break;
		}
	}
	_TimeSinceLastFrame.restart();
}

void Enemy::CheckCollision()
{
	//Check if an enemy gets shooted by the player
	for (unsigned int c = 0; c < static_cast<ParticlePositionAffector*>(_ParticleAffector)->GetParticlePositions()->size(); c++)
	{
		if (_EnemyShip->getTransformedBoundingBox().isPointInside(static_cast<ParticlePositionAffector*>(_ParticleAffector)->GetParticlePositions()->at(c)))
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
			_ParticleEmitter = _ParticleSystem->createBoxEmitter(_EnemyShip->getTransformedBoundingBox(), irr::core::vector3df(0, 0, 0), 500, 500, irr::video::SColor(255, 255, 255, 255),
				irr::video::SColor(255, 255, 255, 255), 1000, 1000, 0, irr::core::dimension2df(0.5f, 0.5f),
				irr::core::dimension2df(1.0f, 1.0f));
			//Set Emitter for the Particle System
			_ParticleSystem->setEmitter(_ParticleEmitter);

			//Create and add particle affector so the particles fly away from the meteor so it looks like a nice explosion
			_ParticleDetractor = _ParticleSystem->createAttractionAffector(irr::core::vector3df(_EnemyShip->getAbsolutePosition().X, _EnemyShip->getAbsolutePosition().Y, _EnemyShip->getAbsolutePosition().Z - 1.0f), 25.0f, false);
			_ParticleSystem->addAffector(_ParticleDetractor);

			//Start Explosion clock (after 50 ms no more particles are spawned)
			_ExplosionClock.restart();

			//The ship is destroyed -> dont show it anymore
			_EnemyShip->setVisible(false); 
		}
	}

	if (_ExplosionClock.getElapsedTime().asMilliseconds() > sf::milliseconds(50).asMilliseconds() && _ParticleEmitter != nullptr)
	{
		_ParticleEmitter->setMaxParticlesPerSecond(0);
		_Alive = false; //Enemy was shot
	}

	//Check if the enemy crashes into the player
	if (_EnemyShip->getTransformedBoundingBox().intersectsWithBox(_Spaceship->getTransformedBoundingBox()))
	{
		_SpaceshipWasHitted = true;
	}
}

