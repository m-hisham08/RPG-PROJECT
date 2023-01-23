#pragma once
#include"States/State.h"
#include"Entities/Entity.h"
#include"Entities/Player.h"
#include"GUI/PauseMenu.h"
#include"Map/TileMap.h"

class GameState :
	public State {
private:
	Player* player;
	PauseMenu* pmenu;

	TileMap* tileMap;

	sf::Font font;

	void initTextures();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initPlayer();
	void initTileMap();
	
public:
	GameState(StateData* state_data);
	virtual ~GameState();

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};