#pragma once
#include"Buttons/Gui.h"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font& font;
	sf::Text menuText;

	std::map<std::string, gui::Button*> buttonContainer;

public:

	//Contructors & Destructors
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();


	//Accessors
	std::map<std::string, gui::Button*>& getButtons();
	const bool isButtonPressed(const std::string key);

	//Functions
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

