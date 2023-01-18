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
}

EditorState::~EditorState()
{
	auto it = buttonContainer.begin();
	for (it = buttonContainer.begin(); it != buttonContainer.end(); ++it) {
		delete it->second;
	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}


void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateButtons();
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