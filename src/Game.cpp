#include "Game.h"


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
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
	this->fullscreen = false;
	this->deltaTime = 0.f;
}

void Game::initWindow()
{
	//intialising a window by loading the arguments or parameters from a text file!
	std::ifstream ifs;
	ifs.open("config/windows.ini");

	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool full_screen = false;
	int set_frame_rate_limit = 60;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) {
		getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> full_screen;
		ifs >> set_frame_rate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}
	else {
		std::cout << "ERROR: GAME.CPP::INITWINDOW() -> UNABLE TO LOAD FILE CONFIG/WINDOWS.INI " << "\n";
	}

	ifs.close();

	this->fullscreen = full_screen;
	windowSettings.antialiasingLevel = antialiasing_level;

	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(set_frame_rate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->statesContainer.push(new MainMenuState(this->window, &this->supportedKeys, &this->statesContainer));
}

void Game::initKeys()
{
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

	if (!this->statesContainer.empty()) {
		this->statesContainer.top()->update(this->deltaTime);

		if (this->statesContainer.top()->getQuit()) {
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
