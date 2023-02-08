#pragma once
#include"Tile/Tile.h"

class TileMap
{
private:
	std::vector < std::vector < std::vector < Tile* > > > map;
	sf::Vector2u maxSize;

	sf::Texture tileSheet;

	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	std::string textureFile;
public:

	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	const sf::Texture* getTileSheet() const;

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void loadFromFile(const std::string file_name);
	void saveToFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget& target);
};

