#pragma once
#include"States\State.h"
#include"States\GameState.h"
#include<States\MainMenuState.h>

class Game
{
private:

	//private variables
	sf::RenderWindow* window;
	sf::Event ev;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock deltaClock;
	float deltaTime;

	std::stack<State*> statesContainer;
	std::map<std::string, int> supportedKeys;

	//initialisation functions
	void initVariables();
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


