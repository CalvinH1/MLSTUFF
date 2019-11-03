
#ifndef Map_
#define Map_
#include <vector>
#include "SFML/Graphics.hpp"

class Map
{


public:

	const int TILE_EMPTY = 1;
	const int TILE_STOP = 0;
	const int TILE_START = 3;
	const int TILE_VISITED = 4;
	const int TILE_END = 5;
	const int TILE_PATH = 2;
	Map(std::pair<int, int> size, int tilesize);
	void draw(sf::RenderWindow* window);
	void reset();
	void clear();
	std::pair<int, int> getSize() const;
	void setMap(std::vector<std::vector<int>> map);
	void setValue(std::pair<int, int> position, int value);
	int getValue(std::pair<int, int> position);
private:
	int tilesize_;
	std::pair<int, int> size_;
	std::vector<std::vector<int>> map_;

};
#endif // Map_
