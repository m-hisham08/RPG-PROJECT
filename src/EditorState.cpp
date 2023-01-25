#include"stdafx.h"
#include "States/EditorState.h"


EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackgrounds();
	this->initKeybinds();
	this->initFonts();
	this->initText();
	this->initButtons();
	this->initPauseMenu();
	this->initTileMap();
	this->initGui();
}

EditorState::~EditorState()
{
	auto it = buttonContainer.begin();
	for (it = buttonContainer.begin(); it != buttonContainer.end(); ++it) {
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;
}

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
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

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("res/Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR: EDITORSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf";
	//throw("ERROR: MAINMENUSTATE.CPP::INITFONTS() -> UNABLE TO LOAD FILE res/Fonts/Dosis-Light.ttf");
}

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setFillColor(sf::Color::White);
}


void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
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

void EditorState::updateEditorInput(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())

		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);

	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())

		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getKeytime())

		if (this->textureRect.left < 800)

			this->textureRect.left += 100;
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::updateGui()
{
	this->selectorRect.setTextureRect(this->textureRect);
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);

	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	std::stringstream ss;
	ss << this->mousePosView.x << " X " << this->mousePosView.y << "\n" << this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());
}


void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateKeytime(dt);
	this->updateMousePositions();

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui();
		this->updateEditorInput(dt);
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

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);

	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->tileMap->render(*target);

	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) {

		this->pmenu->render(*target);

	}
}