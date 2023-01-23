#pragma once
#include"Tile/Tile.h"

class TileMap
{
private:
	std::vector < std::vector < std::vector < Tile* > > > map;
	sf::Vector2u maxSize;


	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
public:

	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	void addTile();
	void removeTile();

	void update();
	void render(sf::RenderTarget& target);
};

