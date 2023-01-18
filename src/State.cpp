#include"stdafx.h"

#include "States\State.h"


State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesContainer)
{
    this->statesContainer = statesContainer;
    this->window = window;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
    this->quit = false;
    this->paused = false;
    this->supportedKeys = supportedKeys;
}

State::~State()
{

}

const bool& State::getQuit() const
{
    return this->quit;
}

const bool State::getKeytime()
{
    if (this->keytime >= this->keytimeMax) {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void State::endState()
{
    this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}


void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateKeytime(const float& dt)
{
    if (this->keytime < keytimeMax)
        this->keytime += 50.f * dt;
}
