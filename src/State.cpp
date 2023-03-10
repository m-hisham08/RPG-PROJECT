#include"stdafx.h"

#include "States\State.h"


State::State(StateData* state_data)
{
    this->stateData = state_data;

    this->statesContainer = state_data->statesContainer;
    this->window = state_data->window;
    this->supportedKeys = state_data->supportedKeys;
    this->gridSize = state_data->gridSize;

    this->keytime = 0.f;
    this->keytimeMax = 10.f;
    this->quit = false;
    this->paused = false;
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


void State::updateMousePositions(sf::View* view)
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    if(view)
        this->window->setView(*view);

    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mousePosGrid = sf::Vector2u(
        static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
        static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
    );

    this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt)
{
    if (this->keytime < keytimeMax)
        this->keytime += 50.f * dt;
}
