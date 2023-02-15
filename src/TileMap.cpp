#include"stdafx.h"

#include"Map/TileMap.h"



void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}this->map[x][y].clear();

		}this->map[x].clear();

	}this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->textureFile = texture_file;
	this->layers = 1;

	this->map.resize(this->maxSize.x, std::vector < std::vector < Tile* > >());
	for (size_t x = 0; x < this->maxSize.x ; x ++)
	{

		for (size_t y = 0; y < this->maxSize.y ; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector < Tile* >());

			for (size_t z = 0; z < this->layers ; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "TILEMAP.CPP :: FAILED TO LOAD THE TEXTURE 'grass1.png' \n";
}

TileMap::~TileMap()
{
	this->clear();
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			this->map[x][y][z] = new Tile(x , y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->textureFile = texture_file;
		this->layers = layers;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector < std::vector < Tile* > >());
		for (size_t x = 0; x < this->maxSize.x; x++)
		{

			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector < Tile* >());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}
		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "TILEMAP.CPP :: FAILED TO LOAD THE TEXTURE 'grass1.png' \n";

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), 
				collision, type);
		}
	}
	else
	{
		std::cout << "ERROR :: TILEMAP :: COULD NOT LOAD THE TILMAP FROM FILE - " << file_name << std::endl;
	}

	in_file.close();

}

void TileMap::saveToFile(const std::string file_name)
{
	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		/*
			SAVES THE ENTIRE TILEMAP TO A TEXT FILE
			DATA THAT WILL BE SAVED:

			** BASIC INFO **
			Size x, y
			gridSize
			layers
			texture_file_path

			** TILE INFO **
			GridSize x y, TextureRect x y, collision, type
		*/

		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " ";
				}
			}
		}

	}
	else
	{
		std::cout << "ERROR :: TILEMAP :: COULD NOT SAVE THE TILMAP TO FILE - " << file_name << std::endl;
	}

	out_file.close();
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z != NULL)
					z->render(target); 

			}

		}

	}
}

