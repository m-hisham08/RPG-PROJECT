#pragma once
#include "States/State.h"
#include "Buttons/Gui.h"

#include<fstream>

class EditorState :
    public State
{
private:
	sf::Font font;

	std::map<std::string, gui::Button*> buttonContainer;

	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer);
	virtual ~EditorState();



	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

