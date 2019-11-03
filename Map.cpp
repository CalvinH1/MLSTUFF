#include "Map.h"
Map::Map(std::pair<int, int> size, int tileSize)
{
	this->size_ = size;
	this->tilesize_ = tileSize;
	map_.resize(size.first, std::vector<int>(size.second, true));
}

void Map::draw(sf::RenderWindow* window)
{
	sf::RectangleShape shape;
	for (int x = 0; x < size_.first; ++x)
	{
		for (int y = 0; y < size_.second; ++y)
		{
			shape.setPosition(x * tilesize_, y * tilesize_);
			shape.setSize(sf::Vector2f(tilesize_, tilesize_));
			shape.setOutlineColor(sf::Color(0, 0, 0));
			shape.setOutlineThickness(1);

			int cellValue = getValue(std::pair<int, int>(x, y));


			if (cellValue == TILE_EMPTY)
			{
				shape.setFillColor(sf::Color(255, 255, 255));
			}
			else if (cellValue == TILE_STOP)
			{
				shape.setFillColor(sf::Color(68, 68, 68));
			}
			else if (cellValue == TILE_END)
			{
				shape.setFillColor(sf::Color(178, 0, 0));
			}
			else if (cellValue == TILE_START)
			{
				shape.setFillColor(sf::Color(0, 140, 35));
			}
			else if (cellValue == TILE_VISITED)
			{
				shape.setFillColor(sf::Color(0, 191, 255));
			}
			else if (cellValue == TILE_PATH)
			{
				shape.setFillColor(sf::Color(0, 74, 35));
			}

			window->draw(shape);
		}
	}
}

void Map::reset()
{
	for (int x = 0; x < size_.first; ++x)
	{
		for (int y = 0; y < size_.second; ++y)
		{
			if (map_[x][y] == TILE_VISITED)
			{
				map_[x][y] = TILE_EMPTY;
			}
			else if (map_[x][y] == TILE_PATH)
			{
				map_[x][y] = TILE_EMPTY;
			}
		}
	}
}

void Map::clear()
{
	for (int x = 0; x < size_.first; ++x)
	{
		for (int y = 0; y < size_.second; ++y)
		{
			map_[x][y] = TILE_EMPTY;
		}
	}
}

std::pair<int, int> Map::getSize() const
{
	return size_;
}

void Map::setMap(std::vector<std::vector<int>> map)
{
	for (int x = 0; x < size_.first; ++x)
	{
		for (int y = 0; y < size_.second; ++y)
		{
			this->map_[x][y] = map[x][y];
		}
	}
}

void Map::setValue(std::pair<int, int> position, int value)
{
	map_[position.first][position.second] = value;
}

int Map::getValue(std::pair<int, int> position)
{
	return map_[position.first][position.second];
}

