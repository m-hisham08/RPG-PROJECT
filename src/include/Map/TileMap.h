#pragma once
#include"Tile/Tile.h"

class TileMap
{
private:
	std::vector < std::vector < std::vector < Tile* > > > map;
	sf::Vector2u maxSize;

	sf::Texture tileTextureSheet;

	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
public:

	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget& target);
};

