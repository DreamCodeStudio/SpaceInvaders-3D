#include "ScoreCounter.h"

void ScoreCounter::Create(irr::scene::ISceneManager *sceneManager)
{
	//Get GUI Environment a
	_GUIEnvironment = sceneManager->getGUIEnvironment();
	//_GUIEnvironment->getSkin()->setFont(_GUIEnvironment->getFont("Data\\Font\\rpgfont.xml")); We already set the font in the Menu class

	//Add the score counter to the gui (it will be placed over the Play Button because Irrlicht uses only one GUI environment. Otherwise we would need to remove and recreate the play button everytime we load the menu)
	_Counter = _GUIEnvironment->addStaticText(irr::core::stringw("").c_str(), irr::core::rect<irr::s32>(50, 50, 200, 90), false, true, 0, -1, true);
	_Counter->setBackgroundColor(irr::video::SColor(255, 130, 130, 130));	//Set background 
	_Counter->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER, irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER);	//Center the text
	_Counter->setVisible(false);		//The user starts in the menu so at start the counter should be invisible
}


void ScoreCounter::Update()
{
	//Set the new text
	_Counter->setText(irr::core::stringw(std::to_string(_ScoreClock.getElapsedTime().asMilliseconds()).c_str()).c_str());

	//Check if the menu was loaded and the game was restartet -> if so restart score counter
	if (_TimeSinceLastFrame.getElapsedTime().asMilliseconds() > sf::milliseconds(300).asMilliseconds()) //The Score counter was not updated for more than 300 ms -> the menu was loaded -> reset score counter
	{
		_ScoreClock.restart();
	}

	_TimeSinceLastFrame.restart();
}

void ScoreCounter::Render()
{
	//Set counter visible and render it. After this make it invisible again
	_Counter->setVisible(true);
	_GUIEnvironment->drawAll();
	_Counter->setVisible(false);	//Make it invisible because if the player collide with a meteor or enemy spaceship the menu starts, where the score counter should be invisible
}