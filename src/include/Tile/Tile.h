#pragma once

enum TileTypes {
	DEFAULT = 0, DAMAGING
};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	short type;
	bool collision;

public:
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT
	);
	virtual ~Tile();

	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};

