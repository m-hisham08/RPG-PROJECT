#pragma once
#include"Tile/Tile.h"

class TileMap
{
private:
	std::vector < std::vector < std::vector < Tile > > > map;
	sf::Vector2u maxSize;

	unsigned gridSizeU;
	unsigned layers;
public:
	TileMap();
	virtual ~TileMap();
};

