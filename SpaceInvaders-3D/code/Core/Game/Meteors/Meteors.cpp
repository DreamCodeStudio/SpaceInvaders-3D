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
}

void Meteors::Update()
{
	if (_SpawnClock.getElapsedTime().asMilliseconds() > sf::milliseconds(2000).asMilliseconds()) //Spawn a meteor after some time
	{
		_Meteors.push_back(_SceneManager->addAnimatedMeshSceneNode(_MeteorMesh, 0, -1, irr::core::vector3df(static_cast<float>((rand() % 44) - 22), static_cast<float>((rand() % 17) - 9), 50.0f))); //Create a meteor on a random position
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
}

/* ####### Private ######## */

void Meteors::CheckCollision()
{
	//Check collision with spaceship for every meteor
	for (unsigned int c = 0; c < _Meteors.size(); c++)
	{
		if (_Meteors[c]->getTransformedBoundingBox().intersectsWithBox(_Spaceship->getTransformedBoundingBox())) //If the spaceship box intersect with the meteor box -> there is a collision
		{
			
		}
	}

	//Check collision with the laser beam
	for (unsigned int c = 0; c < static_cast<ParticlePositionAffector*>(_ParticlePositionAffector)->GetParticlePositions()->size(); c++) //Check all particles 
	{
		for (unsigned int i = 0; i < _Meteors.size(); i++)		//Check all Meteors
		{
			if (_Meteors[i]->getTransformedBoundingBox().isPointInside(static_cast<ParticlePositionAffector*>(_ParticlePositionAffector)->GetParticlePositions()->at(c))) //If the particle is inside the meteor -> collision detected
			{
				_Meteors[i]->remove();
				_Meteors.erase(_Meteors.begin() + i, _Meteors.begin() + i + 1);
				i = 0;
				c = 0;
			}
		}
	}

}