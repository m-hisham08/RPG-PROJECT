#pragma once
#include "States/State.h"
#include "ResourceFiles/Gui.h"
#include"GUI/PauseMenu.h"
#include"Map/TileMap.h"

class TileMap;

class EditorState :
    public State
{
private:
	sf::Font font;
	sf::Text cursorText;

	sf::View view;

	bool collision;
	float cameraSpeed;
	short type;

	PauseMenu* pmenu;

	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	sf::RectangleShape sidebar;

	TileMap* tileMap;
	gui::TextureSelector* textureSelector;

	std::map<std::string, gui::Button*> buttonContainer;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initGui();
	void initView();
	void initFonts();
	void initText();
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
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

