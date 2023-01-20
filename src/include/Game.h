#pragma once
#include"States\State.h"
#include"States\GameState.h"
#include<States\MainMenuState.h>
#include"ResourceFiles/GraphicsSettings.h"

class Game
{
private:

	//private variables
	sf::RenderWindow* window;
	sf::Event ev;

	GraphicsSettings gfxSettings;

	sf::Clock deltaClock;
	float deltaTime;

	std::stack<State*> statesContainer;
	std::map<std::string, int> supportedKeys;

	//initialisation functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStates();
	

public:
	//Constructors and destructors
	Game();
	~Game();

	//misc functions
	void endApplication();

	//functions
	void updateEvents();
	void update();
	void render();
	void updateDT();
	void run();

};


