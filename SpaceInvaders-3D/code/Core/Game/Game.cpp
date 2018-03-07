#include "Game.h"

void Game::Create(irr::IrrlichtDevice *device, irr::scene::ISceneManager *sceneManager)
{
	//Save pointer to parameters
	_SceneManager = sceneManager;
	_Device = device;

	_SceneManager->setAmbientLight(irr::video::SColor(30, 30, 30, 30));

	//Create game camera
	_GameCamera = _SceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 0, -25), irr::core::vector3df(0, 0, 0), -1, true);
	_GameCamera->setFarValue(10000000);
	//_GameCamera = _SceneManager->addCameraSceneNodeFPS();

	//Load 3D-game objects
	_Spaceship = _SceneManager->addAnimatedMeshSceneNode(_SceneManager->getMesh("Data\\Objects\\Spaceship\\Spaceship.obj"), 0, -1, irr::core::vector3df(0, -5, 0), irr::core::vector3df(0, 0, 0));
	_Spaceship->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);

	//Create some light
	irr::scene::ILightSceneNode *light = _SceneManager->addLightSceneNode(0, irr::core::vector3df(0, 0, 0), irr::video::SColor(100, 100, 100, 100));

	//Create particle system
	_ParticleSystem = _SceneManager->addParticleSystemSceneNode(false);
	_ParticleSystem->setMaterialTexture(0, _SceneManager->getVideoDriver()->getTexture("Data\\Textures\\Particle\\fireball.bmp"));
	_ParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_BoxEmitter = _ParticleSystem->createBoxEmitter(irr::core::aabbox3df(_Spaceship->getAbsolutePosition(),
																		 _Spaceship->getAbsolutePosition()), irr::core::vector3df(0, 0, 0), 0, 0, irr::video::SColor(255, 255, 255, 255), 
																																						 irr::video::SColor(255, 255, 255, 255), 2000, 2000, 0, irr::core::dimension2df(1.5f, 1.5f),
																																										    									 irr::core::dimension2df(1.5f, 1.5f));
	_ParticleSystem->setEmitter(_BoxEmitter);
}

int Game::Update()
{
	_Spaceship->setVisible(true);
	_SceneManager->setActiveCamera(_GameCamera);

	//Check here if pause button is pressed
	//If the user exit game -> set spaceship visibility to false


	//Check for user input
	this->CheckMovementInput();  //Player 1
	this->CheckFireInput();		 //Player 2


	return GAME_STATE_RUN;
}

void Game::Render()
{
}

/* ##### Private ##### */

void Game::CheckMovementInput()
{
	//Move the spaceship according to the rotation it has
	_Spaceship->setPosition(irr::core::vector3df(_Spaceship->getAbsolutePosition().X - _Spaceship->getRotation().Z * 0.002f, _Spaceship->getAbsolutePosition().Y - _Spaceship->getRotation().X * 0.002f, _Spaceship->getAbsolutePosition().Z));

	//If the user does not change the rotation on the X-Axis -> rotate back to normal
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		if (_Spaceship->getRotation().X > 0 && _VerticalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
		{
			_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X - 0.3f, 0, _Spaceship->getRotation().Z));
			_VerticalTimer.restart();
		}
		if (_Spaceship->getRotation().X < 0 && _VerticalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
		{
			_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X + 0.3f, 0, _Spaceship->getRotation().Z));
			_VerticalTimer.restart();
		}	
	}

	//If the user does not change the rotation on the Z-Axis -> rotate back to normal
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		if (_Spaceship->getRotation().Z > 0 && _HorizontalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
		{
			_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z - 0.3f));
			_HorizontalTimer.restart();
		}
		if (_Spaceship->getRotation().Z < 0 && _HorizontalTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(5).asMilliseconds())
		{
			_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z + 0.3f));
			_HorizontalTimer.restart();
		}
	}

	/* ################# Check if the user wants to go up or down #################### */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //If the user wants to go down
	{
		if (_Spaceship->getAbsolutePosition().Y > -9.0f)  //Slowly rotate the "nose" of the ship to the ground
		{
			if (_VerticalTimer.getElapsedTime().asMilliseconds() < sf::milliseconds(5).asMilliseconds())
			{
				return;
			}

			if (_Spaceship->getRotation().X < 45)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X + 0.3f, 0, _Spaceship->getRotation().Z)); //Rotate
			}

			_VerticalTimer.restart();
		}
		else //If the user hits the border of the screen
		{
			if (_Spaceship->getRotation().X > 0)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X - 0.3f, 0, _Spaceship->getRotation().Z)); //Rotate
			}
		}

		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //If the user wants to go down
	{
		if (_Spaceship->getAbsolutePosition().Y < 6.0f)  //Slowly rotate the "nose" of the ship to the ground
		{
			if (_VerticalTimer.getElapsedTime().asMilliseconds() < sf::milliseconds(5).asMilliseconds())
			{
				return;
			}
			
			if (_Spaceship->getRotation().X > -45)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X - 0.3f, 0, _Spaceship->getRotation().Z)); //Rotate
			}

			_VerticalTimer.restart();
		}
		else  //If the user hits the border of the screen
		{
			if (_Spaceship->getRotation().X < -0.3f)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X + 0.3f , 0, _Spaceship->getRotation().Z)); //Rotate
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
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z + 0.3f)); //Rotate
			}

			_HorizontalTimer.restart();
		}
		else   //If the user hits the border of the screen
		{
			if (_Spaceship->getRotation().Z > 0)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z - 0.3f)); //Rotate
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
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z - 0.3f)); //Rotate
			}

			_HorizontalTimer.restart();
		}
		else    //If the user hits the border of the screen
		{
			if (_Spaceship->getRotation().Z < 0)
			{
				_Spaceship->setRotation(irr::core::vector3df(_Spaceship->getRotation().X, 0, _Spaceship->getRotation().Z + 0.3f)); //Rotate
			}
		}

		return;
	}
}

void Game::CheckFireInput()
{
	//If the user wants to fire a laser
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _FireCooldown.getElapsedTime().asMilliseconds() > sf::milliseconds(750).asMilliseconds())
	{		
		_BoxEmitter->setMinParticlesPerSecond(1000);
		_BoxEmitter->setMaxParticlesPerSecond(1000);

		//First get the screen ray
		irr::core::vector3df directionVector = _SceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _SceneManager->getActiveCamera()).getVector();
		directionVector.normalize();

		_BoxEmitter->setBox((irr::core::aabbox3df(_Spaceship->getAbsolutePosition(), _Spaceship->getAbsolutePosition())));

		_BoxEmitter->setDirection(directionVector);

		_FireCooldown.restart();	//A cooldown for the user so he can not hold the fire key
		_LaserTimer.restart(); //Wait 0.2 seconds than destroy box emitter so you get a nice small laser beam
	}

	if (_LaserTimer.getElapsedTime().asMilliseconds() > sf::milliseconds(200).asMilliseconds())
	{
		_BoxEmitter->setMaxParticlesPerSecond(0);
	}
}