#pragma once
#include "States/State.h"
#include "ResourceFiles/Gui.h"
#include"GUI/PauseMenu.h"
#include"Map/TileMap.h"

class EditorState :
    public State
{
private:
	sf::Font font;

	PauseMenu* pmenu;

	TileMap map;

	std::map<std::string, gui::Button*> buttonContainer;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initButtons();
	void initPauseMenu();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer);
	virtual ~EditorState();



	void updateButtons();
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

