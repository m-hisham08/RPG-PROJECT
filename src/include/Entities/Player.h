#pragma once
#include "Entities/Entity.h"

class Player :
    public Entity
{
private:
    bool attacking;

    void initComponents();
    void initVariables();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    ~Player();

    void updateAttack();
    void updateAnimations(const float& dt);

    virtual void update(const float& dt);

};

