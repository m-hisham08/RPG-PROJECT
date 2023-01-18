#include"stdafx.h"

#include"States/GameState.h"


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer) 
	: State(window, supportedKeys, statesContainer)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayer();
	
	std::cout << "New gamestate" << "\n";
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

void GameState::initTextures()
{
	
	if (!this->textureMap["PLAYER_SHEET"].loadFromFile("res/Player/PLAYER_SHEET.png")) {
		std::cout << "ERROR :: GAMESTATE :: CANNOT LOAD PLAYER TEXTURE" << "\n";
		throw("ERROR :: GAMESTATE :: CANNOT LOAD PLAYER TEXTURE");
	}
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("res/Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR: MAINMENUSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf";
	//throw("ERROR: MAINMENUSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf");
}

void GameState::initKeybinds()
{
	std::ifstream ifs;
	ifs.open("config/gamestate_keybinds.ini");

	if (ifs.is_open()) {
		std::string keys;
	    std::string keys2;
		while (ifs >> keys >> keys2) {
			this->keybinds[keys] = this->supportedKeys->at(keys2);
		}
	}

	ifs.close();

}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0, this->textureMap["PLAYER_SHEET"]);
}

void GameState::updateInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);

}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}


void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) {
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->player->render(*target);

	if (this->paused) {
		this->pmenu->render(*target);
	}
}

