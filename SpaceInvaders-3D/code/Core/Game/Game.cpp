#include "Game.h"

void Game::Create(irr::scene::ISceneManager *sceneManager)
{
	//Save pointer to scene manager
	_SceneManager = sceneManager;

	//Create game camera
	_GameCamera = _SceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 0, -25), irr::core::vector3df(0, 0, 0), -1, true);

	//Load 3D-game objects
	_Spaceship = _SceneManager->addAnimatedMeshSceneNode(_SceneManager->getMesh("Data\\Objects\\Spaceship\\Spaceship.obj"), 0, -1, irr::core::vector3df(0, -5, 0), irr::core::vector3df(0, 0, 0));
	_Spaceship->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);

	irr::scene::ILightSceneNode *light = _SceneManager->addLightSceneNode(0, irr::core::vector3df(0, 0, 0), irr::video::SColor(100, 100, 100, 100));

	_GameCamera->setTarget(_Spaceship->getAbsolutePosition());
}

int Game::Update()
{
	_Spaceship->setVisible(true);
	_SceneManager->setActiveCamera(_GameCamera);

	//Check here if pause button is pressed
	//If the user exit game -> set spaceship visibility to false


	//Check for user input
	this->CheckUserInput();

	return GAME_STATE_RUN;
}

void Game::Render()
{

}

/* ##### Private ##### */

void Game::CheckUserInput()
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_VerticalMovement = MOVEMENT::UP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_VerticalMovement = MOVEMENT::DOWN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_HorizontalMovement = MOVEMENT::LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_HorizontalMovement = MOVEMENT::RIGHT;
	}*/


	/* ################# Check if the user wants to go up or down #################### */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //If the user wants to go down
	{
		if (_Spaceship->getAbsolutePosition().Y > -15.14f)  //Slowly rotate the "nose" of the ship to the ground
		{
			if (_VerticalTimer.getElapsedTime().asMilliseconds() < sf::milliseconds(5).asMilliseconds())
			{
				return;
			}

			if (_Spaceship->getRotation().X < 45)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X + 0.2f, 0, _Spaceship->getRotation().Z)); //Rotate
			}

			_Spaceship->setPosition(irr::core::vector3df(_Spaceship->getAbsolutePosition().X, _Spaceship->getAbsolutePosition().Y - _Spaceship->getRotation().X * 0.002f, _Spaceship->getAbsolutePosition().Z));

			_VerticalTimer.restart();
		}
		else
		{
			if (_Spaceship->getRotation().X > 0)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X - 0.2f, 0, _Spaceship->getRotation().Z)); //Rotate
			}
		}

		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //If the user wants to go down
	{
		if (_Spaceship->getAbsolutePosition().Y < 8.0f)  //Slowly rotate the "nose" of the ship to the ground
		{
			if (_VerticalTimer.getElapsedTime().asMilliseconds() < sf::milliseconds(5).asMilliseconds())
			{
				return;
			}
			
			if (_Spaceship->getRotation().X > -45)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X - 0.2f, 0, _Spaceship->getRotation().Z)); //Rotate
			}
			_Spaceship->setPosition(irr::core::vector3df(_Spaceship->getAbsolutePosition().X, _Spaceship->getAbsolutePosition().Y - _Spaceship->getRotation().X * 0.002f, _Spaceship->getAbsolutePosition().Z));

			_VerticalTimer.restart();
		}
		else
		{
			if (_Spaceship->getRotation().X < -0.2f)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X , 0, _Spaceship->getRotation().Z)); //Rotate
			}
		}

		return;
	}

	/* ################# Check if the user wants to go right or left #################### */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //If the user wants to go down
	{
		if (_Spaceship->getAbsolutePosition().X > -22.0f)  //Slowly rotate the "nose" of the ship to the ground
		{
			if (_HorizontalTimer.getElapsedTime().asMilliseconds() < sf::milliseconds(5).asMilliseconds())
			{
				return;
			}

			if (_Spaceship->getRotation().Z < 45)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z + 0.2f)); //Rotate
			}
			_Spaceship->setPosition(irr::core::vector3df(_Spaceship->getAbsolutePosition().X - _Spaceship->getRotation().Z * 0.002f, _Spaceship->getAbsolutePosition().Y, _Spaceship->getAbsolutePosition().Z));

			_HorizontalTimer.restart();
		}
		else
		{
			if (_Spaceship->getRotation().Z > 0)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z - 0.2f)); //Rotate
			}
		}

		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //If the user wants to go down
	{
		if (_Spaceship->getAbsolutePosition().X < 22.0f)  //Slowly rotate the "nose" of the ship to the ground
		{
			if (_HorizontalTimer.getElapsedTime().asMilliseconds() < sf::milliseconds(5).asMilliseconds())
			{
				return;
			}

			if (_Spaceship->getRotation().Z > -45)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z - 0.2f)); //Rotate
			}
			_Spaceship->setPosition(irr::core::vector3df(_Spaceship->getAbsolutePosition().X - _Spaceship->getRotation().Z * 0.002f, _Spaceship->getAbsolutePosition().Y, _Spaceship->getAbsolutePosition().Z));

			_HorizontalTimer.restart();
		}
		else
		{
			if (_Spaceship->getRotation().Z < 0)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z + 0.2f)); //Rotate
			}
		}

		return;
	}

	if (_Spaceship->getRotation().X > 0 && _HorizontalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
	{
		_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X - 0.2f, 0, _Spaceship->getRotation().Z));
		_HorizontalTimer.restart();
	}
	if (_Spaceship->getRotation().X < 0 && _HorizontalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
	{
		_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X + 0.2f, 0, _Spaceship->getRotation().Z));
		_HorizontalTimer.restart();
	}
	if (_Spaceship->getRotation().Z > 0 && _VerticalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
	{
		_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z - 0.2f));
		_HorizontalTimer.restart();
	}
	if (_Spaceship->getRotation().Z < 0 && _VerticalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
	{
		_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z + 0.2f));
		_HorizontalTimer.restart();
	}

}