#pragma once

#include"Entities/Player.h"
#include"ResourceFiles/GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData {
public:

	StateData() {};

	float gridSize;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	GraphicsSettings* gfxSettings;
	std::stack<State*>* statesContainer;

};

class State
{
private:

protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::stack<State*>* statesContainer;

	StateData* stateData;

	bool quit;
	bool paused;

	float keytime;
	float keytimeMax;

	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	std::map<std::string,sf::Texture> textureMap;

	//protected functions
	virtual void initKeybinds() = 0;


public:
	//Constructors and destructors
	State(StateData* state_data);
	virtual ~State();

	//setters or getters
	void endState();

	//accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//non virtual functions
	void pauseState();
	void unpauseState();

	//pure virtual functions
	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

