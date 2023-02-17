#include"stdafx.h"
#include "States/EditorState.h"


EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackgrounds();
	this->initView();
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

	delete this->textureSelector;
}

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 100.f;
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
	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);


	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 700.f, 300.f,
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font, "Tiles"
	);
}

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width/2.f,
			this->stateData->gfxSettings->resolution.height/2.f
		)
		);
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

	this->pmenu->addButton("SAVE", 300.f, "Save");

	this->pmenu->addButton("QUIT", 500.f, "Quit");

	this->pmenu->addButton("LOAD", 100.f, "Load");
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "res/Tiles/tilesheet1.png");
}

void EditorState::initButtons()
{
	
}

void EditorState::updateButtons()
{
	for (auto& it : this->buttonContainer) {
		it.second->update(this->mousePosWindow);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
		{
			if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
			{
				if (!this->textureSelector->getActive())
				{
					this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
				}
			}
		}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
	{
		++this->type;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if(this->type > 0)
			--this->type; 
	}
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("text.slmp");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("text.slmp");
}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	this->cursorText.setPosition(this->mousePosView.x + 100, this->mousePosView.y - 50);
	std::stringstream ss;
	ss << this->mousePosView.x << " X " << this->mousePosView.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type;
		;
	this->cursorText.setString(ss.str());

}


void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateKeytime(dt);
	this->updateMousePositions(&this->view);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
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
	if (this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);
	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->setView(this->view);
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGui(*target);

	if (this->paused) {

		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);

	}
}