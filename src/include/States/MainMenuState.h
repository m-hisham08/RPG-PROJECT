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

	GraphicsSettings& gfxSettings;

	std::map<std::string, gui::Button*> buttonContainer;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer);
	virtual ~MainMenuState();



	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

