#pragma once
#include "States/State.h"
#include"ResourceFiles/Gui.h"
#include"States/GameState.h"
#include"States/EditorState.h"
#include"States/SettingsState.h"
#include"ResourceFiles/GraphicsSettings.h"

class MainMenuState :
    public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttonContainer;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initButtons();

public:
	MainMenuState(StateData* state_Data);
	virtual ~MainMenuState();



	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

