#include"stdafx.h"

#include "MovementComponent/MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	:sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state)
{
	switch (state) {
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//acceleration
	this->velocity.x += acceleration * dir_x;
	this->velocity.y += acceleration * dir_y;

	if (this->velocity.x > 0.f) //check for right
	{
		
	}

	if (this->velocity.x < 0.f) //check for left
	{ 
		
	}
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;

}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

void MovementComponent::update(const float& dt)
{
	//deceleration
	if (this->velocity.x > 0.f) //check for right
	{
		//check for max velocity along positive x
		if (this->velocity.x > maxVelocity)
			this->velocity.x = this->maxVelocity;

		//deceleration along positive x
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
		
	}

	else if (this->velocity.x < 0.f) //check for left
	{
		//check for max velocity along negative x
		if (this->velocity.x < -maxVelocity)
			this->velocity.x = -maxVelocity;

		//deceleration along negative x
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //check for down
	{
		//check for max velocity along positive y
		if (this->velocity.y > maxVelocity)
			this->velocity.y = this->maxVelocity;

		//deceleration along positive y
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}

	else if (this->velocity.y < 0.f) //check for up
	{
		//check for max velocity along negative y
		if (this->velocity.y < -maxVelocity)
			this->velocity.y = -maxVelocity;

		//deceleration along negative y
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//final move
	this->sprite.move(this->velocity * dt);
}
