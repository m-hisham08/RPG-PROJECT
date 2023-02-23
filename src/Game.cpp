#include"stdafx.h"

#include "Game.h"


Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->statesContainer.empty()) {
		delete this->statesContainer.top();
		this->statesContainer.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending the application! \n";
}

void Game::initVariables()
{
	this->window = NULL;
	this->deltaTime = 0.f;
	this->gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("config/graphics.ini");
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.statesContainer = &this->statesContainer;
	this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
	if (this->gfxSettings.fullscreen)

		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings
		);

	else
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initStates()
{
	this->statesContainer.push(new MainMenuState(&this->stateData));
}

void Game::initKeys()
{
	//Creating a SFML window!

	std::ifstream ifs;
	ifs.open("config/game_supportedKeys.ini");

	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	//DEBUG REMOVE LATER
	for (auto i : supportedKeys) {
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->updateEvents();

	if (!this->statesContainer.empty() && this->window->hasFocus())
	{
		this->statesContainer.top()->update(this->deltaTime);

		if (this->statesContainer.top()->getQuit()) 
		{	
			this->statesContainer.top()->endState();
			delete this->statesContainer.top();
			this->statesContainer.pop();
		}
	}

	else {
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	if (!this->statesContainer.empty())
		this->statesContainer.top()->render();

	this->window->display();
}

void Game::updateDT()
{
	this->deltaTime = this->deltaClock.restart().asSeconds();
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->updateDT();
		this->update();
		this->render();
	}
}
