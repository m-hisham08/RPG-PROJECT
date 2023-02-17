#include"stdafx.h"

#include "States/SettingsState.h"



void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackgrounds()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("res/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BAKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("res/Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	} 

	ifs.close();
}

void SettingsState::initGui()
{
	//Buttons
	this->buttonContainer["BACK"] = new gui::Button(
		800.f, 595.f,
		250.f, 65.f,
		&this->font, "Back", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttonContainer["APPLY"] = new gui::Button(
		1000.f, 600.f,
		250.f, 65.f,
		&this->font, "Apply", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


	std::vector<std::string> modes_str;

	for (auto& i : this->modes) {
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}

	//Drop down lists
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		400.f, 300.f, 250.f, 50.f, font, modes_str.data(), modes_str.size()
	);
}

void SettingsState::initText()
{
	//Text init
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 300.f));
	this->optionsText.setCharacterSize(35);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n "
	);
}


SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttonContainer.begin();
	for (it = this->buttonContainer.begin(); it != this->buttonContainer.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Updates all the gui elements in the state and handle their functionlaity.*/
	//Buttons
	for (auto& it : this->buttonContainer)
	{
		it.second->update(this->mousePosWindow);
	}

	//Button functionality
	//Quit the game
	if (this->buttonContainer["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttonContainer["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	//Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttonContainer)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}