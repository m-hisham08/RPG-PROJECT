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

	StateData stateData;

	sf::Clock deltaClock;
	float deltaTime;

	float gridSize;

	std::stack<State*> statesContainer;
	std::map<std::string, int> supportedKeys;

	//initialisation functions
	void initVariables();
	void initGraphicsSettings();
	void initStateData();
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


