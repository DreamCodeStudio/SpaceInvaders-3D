#pragma once
#include <irrlicht.h>
#include <SFML\Graphics.hpp>

class ScoreCounter
{
	public:

		void Create(irr::scene::ISceneManager *sceneManager);

		void Update();
		void Render();

	private:


		irr::gui::IGUIEnvironment *_GUIEnvironment;
		irr::gui::IGUIStaticText *_Counter;
		sf::Clock _ScoreClock;
		sf::Clock _TimeSinceLastFrame;
};