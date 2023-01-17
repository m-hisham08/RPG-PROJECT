#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>

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

