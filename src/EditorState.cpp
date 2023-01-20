#include"stdafx.h"
#include "States/EditorState.h"


EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer)
	: State(window, supportedKeys, statesContainer)
{
	this->initVariables();
	this->initBackgrounds();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->initPauseMenu();
}

EditorState::~EditorState()
{
	auto it = buttonContainer.begin();
	for (it = buttonContainer.begin(); it != buttonContainer.end(); ++it) {
		delete it->second;
	}

	delete this->pmenu;
}

void EditorState::initVariables()
{

}

void EditorState::initBackgrounds()
{

}

void EditorState::initKeybinds()
{
	std::ifstream ifs;
	ifs.open("config/editorstate_keybinds.ini");

	if (ifs.is_open()) {
		std::string keys;
		std::string keys2;
		while (ifs >> keys >> keys2) {
			this->keybinds[keys] = this->supportedKeys->at(keys2);
		}
	}

	ifs.close();

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("res/Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR: EDITORSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf";
	//throw("ERROR: MAINMENUSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf");
}


void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void EditorState::initButtons()
{
	
}

void EditorState::updateButtons()
{
	for (auto& it : this->buttonContainer) {
		it.second->update(this->mousePosView);
	}
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}


void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateKeytime(dt);
	this->updateMousePositions();

	if (!this->paused)
	{
		this->updateButtons();
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttonContainer) {
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderButtons(*target);
	this->map.render(*target);

	if (this->paused) {

		this->pmenu->render(*target);

	}

	//DEBUG REMOVE LATER!!
	sf::Text mouseText;
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	std::stringstream ss;
	ss << this->mousePosView.x << " X " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);

}