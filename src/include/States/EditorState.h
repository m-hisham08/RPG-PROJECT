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

	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	TileMap* tileMap;

	std::map<std::string, gui::Button*> buttonContainer;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initGui();
	void initFonts();
	void initButtons();
	void initPauseMenu();
	void initTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();



	void updateButtons();
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updatePauseMenuButtons();
	void updateGui();
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

