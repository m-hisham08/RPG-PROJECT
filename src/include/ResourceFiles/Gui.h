#pragma once

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

namespace gui {

	class Button
	{
	private:
		sf::Font* font;
		sf::Text text;
		sf::RectangleShape shape;

		short unsigned buttonState;
		short unsigned id;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
	public:
		Button(float x, int y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0
		);

		~Button();

		//accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;
		

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);


	};

	class DropDownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector <gui::Button*> list;

		bool showList;

		float keytime;
		float keytimeMax;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		virtual ~DropDownList();

		//Setters & Getters
		const bool getKeytime();
		const short unsigned& getActiveElementId() const;

		void updateKeytime(const float& dt);

		//functions
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);

	};

	class TextureSelector
	{
	private:
		sf::RectangleShape bounds;
		sf::Sprite sheet;

		float keytime;
		float keytimeMax;
		bool active;
		bool hidden;
		float gridSize;

		gui::Button* hide_btn;
		 
		sf::Vector2u mousePosGrid;
		sf::RectangleShape selector;
		sf::IntRect textureRect;


	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		void updateKeytime(const float& dt);
		void update(const sf::Vector2i mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	
	};
}

