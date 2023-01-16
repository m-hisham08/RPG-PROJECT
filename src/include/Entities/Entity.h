#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include"MovementComponent/MovementComponent.h"
#include"AnimationComponent/AnimationComponent.h"
#include"HitboxComponent/HitboxComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
public:
	Entity();
	~Entity();

	void setTexture(sf::Texture& texture);

	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite,
							float offset_x, float offset_y,
							float width, float height);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

