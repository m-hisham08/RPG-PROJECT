#pragma once

#include "States/State.h"
#include"ResourceFiles/Gui.h"
#include"ResourceFiles/GraphicsSettings.h"

class SettingsState :
    public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;


	std::map<std::string, gui::Button*> buttonContainer;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initGui();
	void initText();

public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //accessors

    //Functions
	void updateGui(const float& dt);
	void updateInput(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

