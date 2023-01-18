#pragma once
#include"States/State.h"
#include"Entities/Entity.h"
#include"Entities/Player.h"
#include"GUI/PauseMenu.h"

class GameState :
	public State {
private:
	Player* player;
	PauseMenu* pmenu;

	sf::Font font;

	void initTextures();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initPlayer();
	
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer);
	virtual ~GameState();

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};