#pragma once

class AnimationComponent
{
private:
	class Animation {
	public:
		sf::Sprite& sprite; 
		sf::Texture& textureSheet;

		bool done;

		float timer;
		float animationTimer = 0.f;

		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
		int width = 0;
		int height = 0;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), timer(0.f), done(false),
			  width(width), height(height)
		{
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frame_x * width, frame_y * height, width, height);

			this->sprite.setTexture(this->textureSheet);
			this->sprite.setTextureRect(this->startRect);
		}

		~Animation() {

		}

		const bool& isDone() const {
			return this->done;
		}

		const bool& play(const float& dt) {

			this->done = false;

			this->timer += 100.0 * dt;

			if (this->timer > this->animationTimer) {

				this->timer = 0.f;

				if (this->currentRect != this->endRect) {

					this->currentRect.left += this->width;

				}
				else {

					this->currentRect.left = this->startRect.left;
					this->done = true;

				}
				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}

		const bool& play(const float& dt, float mod_percent) {

			this->done = false;

			if (mod_percent < 0.7f)
				mod_percent = 0.7f;

			this->timer += mod_percent * 100.0 * dt;

			if (this->timer > this->animationTimer) {

				this->timer = 0.f;

				if (this->currentRect != this->endRect) {

					this->currentRect.left += this->width;

				}
				else {

					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}

		void reset() {

			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};
	
	sf::Texture& textureSheet;
	sf::Sprite& sprite;

	Animation* lastAnimation;
	Animation* priorityAnimation;

	std::map<std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	const bool& isDone(const std::string key);

	void addAnimation(const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height);


	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);

};

