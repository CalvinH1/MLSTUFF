#include "AStar.h"

void Astar::sortByLowestF(std::deque<Node>& deque) const
{
	LessF sortMethod;
	std::sort(deque.begin(), deque.end(), sortMethod);
}

int Astar::getDiagDistance(const std::pair<int, int>& start, const std::pair<int, int>& end) const
{
	int dx = abs(end.first - start.first);
	int dy = abs(end.second - start.second);
	return ((dx+dy) * 10) + ((14-2*10)*std::min(dx,dy));
}

int Astar::getMovementCost(const std::pair<int, int> &start, const std::pair<int, int> &end) const
{
	return start.first != end.first && start.second != end.second ? COST_DIAGONAL : COST_NONDIAGONAL;
}

std::vector<Node> Astar::getNeighbors(const Node &node, Map &map)
{
	std::vector<Node> neighbors;
	std::pair<int, int> prev = node.getPosition();
	std::pair<int, int> nodepos(0, 0);
	std::pair<int, int> mapSize = map.getSize();

	if (prev.second + 1 < mapSize.second)
	{
		nodepos = std::pair<int, int>(prev.first , prev.second + 1);
		neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // East
	}

	if (prev.second - 1 >= 0)
	{
		nodepos = std::pair<int, int>(prev.first, prev.second - 1);
		neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // West
	}
	if (prev.first - 1 >= 0)
	{
		nodepos = std::pair<int, int>(prev.first-1, prev.second );//NORTH
		neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr));
		if (prev.second + 1 < mapSize.second)
		{
			nodepos = std::pair<int, int>(prev.first - 1, prev.second + 1);
			neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // North East
		}
		if (prev.second - 1 >= 0)
		{
			nodepos = std::pair<int, int>(prev.first - 1, prev.second - 1);
			neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // North West
		}
	}
	if (prev.first + 1 < mapSize.first)
	{
		nodepos = std::pair<int, int>(prev.first+1, prev.second);
		neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // South
		if (prev.second + 1 < mapSize.second)
		{
			nodepos = std::pair<int, int>(prev.first + 1, prev.second + 1);
			neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // South East
		}
		if (prev.second - 1 >= 0)
		{
			nodepos = std::pair<int, int>(prev.first + 1, prev.second - 1);
			neighbors.push_back(Node(nodepos, map.getValue(nodepos), nullptr)); // South West
		}
	}

	return neighbors;
}

bool Astar::IsOnList(const Node &node, const std::deque<Node> &list)
{
	return std::find(list.begin(), list.end(), node) != list.end();
}

std::stack<std::pair<int, int>> Astar::findPath(Map &map, const std::pair<int, int> &start, const std::pair<int, int> &end)
{
	std::stack<std::pair<int, int>> path;
	std::deque<Node> openset;
	std::deque<Node> closedset;

	if (start == end)
	{
		return path;
	}

	if (map.getValue(end) == 0)
	{
		return path;
	}

	openset.push_front(Node(start, map.getValue(start), nullptr));

	while (openset.size() > 0)
	{
		sortByLowestF(openset);//find the smallest F score
		Node* currentNode = new Node(openset.front());
		openset.pop_front();
		closedset.push_back(*currentNode);

		if (currentNode->getPosition() == end)
		{
			break;
		}

		std::vector<Node> neighbors = getNeighbors(*currentNode, map);

		for (auto& neighbor : neighbors)
		{
			if (!neighbor.isTraversable() || IsOnList(neighbor, closedset))//if on closed set go next
			{
				continue;
			}

			if (IsOnList(neighbor, openset))// if on openset fix Open set
			{
				int newG = currentNode->getG() + getMovementCost(currentNode->getPosition(), neighbor.getPosition());
				if (newG < neighbor.getG())
				{
					neighbor.setG(newG);
					neighbor.setPrev(currentNode);
				}
			}
			else
			{ //ADD new neighbors openset
				neighbor.setPrev(currentNode);
				neighbor.setH(getDiagDistance(neighbor.getPosition(), end));
				neighbor.setG(currentNode->getG() + getMovementCost(currentNode->getPosition(), neighbor.getPosition()));
				openset.push_front(neighbor);
				map.setValue(neighbor.getPosition(), map.TILE_VISITED);
			}
		}
	}

	Node* pathNode = &closedset.back();
	while (pathNode != nullptr)
	{
		path.push(pathNode->getPosition());
		pathNode = pathNode->getPrev();
	}

	return path;
}


