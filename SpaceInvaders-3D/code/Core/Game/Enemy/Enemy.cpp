#include "Enemy.h"

void Enemy::Create(irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *spaceship)
{
	//Seed for random number generation
	srand(static_cast<unsigned int>(time(NULL)));

	//Save pointer to parameter
	_SceneManager = sceneManager;
	_Spaceship = spaceship;

	//Create Enemy spaceship
	_EnemyShip = _SceneManager->addAnimatedMeshSceneNode(_SceneManager->getMesh("Data\\Objects\\EnemySpaceship\\EnemySpaceship.obj"), 0, -1, irr::core::vector3df(static_cast<float>((rand() % 44) - 22), /*static_cast<float>((rand() % 17) - 9)*/ 9, 100.0f)); 

	//Set random direction at start
	_VerticalMovement = rand() % 2;
	_HorizontalMovement = rand() % 2 + 2;
}

void Enemy::Update()
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