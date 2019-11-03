#include <SFML/Graphics.hpp>
#include <deque>
#include <queue>
#include <stack>
#include "Map.h"
#include "Node.h"
#include "AStar.h"



bool mouseWithinWindow(sf::RenderWindow &window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	return mousePosition.x > 0 && mousePosition.x < window.getSize().x && mousePosition.y > 0 && mousePosition.y < window.getSize().y;
}

int main()
{
	const int TILE_SIZE = 25;
	const int TILES_X = 55;
	const int TILES_Y = 30;
	const int WIN_X = TILES_X * TILE_SIZE;
	const int WIN_Y = TILES_Y * TILE_SIZE;
	Map map(std::pair<int, int>(TILES_X, TILES_Y), TILE_SIZE);

	std::pair<int, int> startPosition(1, 1);
	std::pair<int, int> destination(2, 1);

	Astar pf;

	sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y), "A* Path Finding", sf::Style::Close);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && mouseWithinWindow(window))
			{
				std::pair<int, int> mouseToArray = std::pair<int, int>(sf::Mouse::getPosition(window).x / TILE_SIZE, sf::Mouse::getPosition(window).y / TILE_SIZE);
				switch (event.key.code)
				{
				case sf::Keyboard::S:
					map.setValue(startPosition, map.TILE_EMPTY);
					map.setValue(mouseToArray, map.TILE_START);
					startPosition = mouseToArray;
					break;
				case sf::Keyboard::E:
					map.setValue(destination, map.TILE_EMPTY);
					map.setValue(mouseToArray, map.TILE_END);
					destination = mouseToArray;
					break;
				case sf::Keyboard::C:
					map.clear();
					break;
				case sf::Keyboard::Space:
					map.reset();
					std::stack<std::pair<int, int>> path = pf.findPath(map, startPosition, destination);
					while (path.size() > 0)
					{
						std::pair<int, int> point = path.top();
						map.setValue(point, map.TILE_PATH);
						path.pop();
					}
					map.setValue(startPosition, map.TILE_START);
					map.setValue(destination, map.TILE_END);
					break;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseWithinWindow(window))
		{
			std::pair<int, int>mouseToArray = std::pair<int, int>(sf::Mouse::getPosition(window).x / TILE_SIZE, sf::Mouse::getPosition(window).y / TILE_SIZE);
			map.setValue(mouseToArray, map.TILE_STOP);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouseWithinWindow(window))
		{
			std::pair<int, int> mouseToArray = std::pair<int, int>(sf::Mouse::getPosition(window).x / TILE_SIZE, sf::Mouse::getPosition(window).y / TILE_SIZE);
			map.setValue(mouseToArray, map.TILE_EMPTY);
		}

		window.clear();

		map.draw(&window);

		window.display();


	}

}