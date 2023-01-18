#include"stdafx.h"

#include "States/MainMenuState.h"



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer)
	: State(window, supportedKeys, statesContainer)
{
	this->initVariables();
	this->initBackgrounds();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = buttonContainer.begin();
	for (it = buttonContainer.begin(); it != buttonContainer.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackgrounds()
{
	if (!this->backgroundTexture.loadFromFile("res/Backgrounds/bg1.png")) {
		std::cout << "ERROR :: MAINMENUSTATE :: CANNOT LOAD BACKGROUND TEXTURE" << "\n";
		throw("ERROR::MAINMENUSTATE::CANNOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backgroundTexture);
	this->background.setSize(
		sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
		)
	);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs;
	ifs.open("config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string keys;
		std::string keys2;
		while (ifs >> keys >> keys2) {
			this->keybinds[keys] = this->supportedKeys->at(keys2);
		}
	}

	ifs.close();

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("res/Fonts/Dosis-Light.ttf")) {
		std::cout << "ERROR: MAINMENUSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf";
		throw("ERROR: MAINMENUSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf");
	}
}

void MainMenuState::initButtons()
{
	this->buttonContainer["GAME_STATE"] = new gui::Button(
		160.f, 340.f, 250.f, 50.f,
		&this->font, "New Game", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttonContainer["EDITOR_STATE"] = new gui::Button(
		160.f, 440.f, 250.f, 50.f,
		&this->font, "Editor", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttonContainer["SETTINGS_STATE"] = new gui::Button(
		160.f, 540.f, 250.f, 50.f,
		&this->font, "Settings", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	
	this->buttonContainer["EXIT_STATE"] = new gui::Button(
		160.f, 640.f, 250.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttonContainer) {
		it.second->update(this->mousePosView);
	}

	

	if (this->buttonContainer["GAME_STATE"]->isPressed()) {
		this->statesContainer->push(new GameState(this->window, this->supportedKeys, this->statesContainer));
	}

	if (this->buttonContainer["SETTINGS_STATE"]->isPressed()) {
		this->statesContainer->push(new SettingsState(this->window, this->supportedKeys, this->statesContainer));
	}

	if (this->buttonContainer["EDITOR_STATE"]->isPressed()) {
		this->statesContainer->push(new EditorState(this->window, this->supportedKeys, this->statesContainer));
	}

	if (this->buttonContainer["EXIT_STATE"]->isPressed()) {
		this->endState();
	}

}

void MainMenuState::updateInput(const float& dt)
{
	
}


void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttonContainer) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(*target);

	//DEBUG REMOVE LATER!!
	/*sf::Text mouseText;
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	std::stringstream ss;
	ss << this->mousePosView.x << " X " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/

}