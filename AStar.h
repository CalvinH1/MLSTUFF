#ifndef Astar_
#define Astar_
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include "Node.h"
#include "Map.h"
#include <iostream>
struct LessF
{
	bool operator() (const Node &n1, const Node &n2) const
	{
		return n1.getF() < n2.getF();
	}
};

class Astar
{

public:

	std::stack<std::pair<int, int>> findPath(Map &map, const std::pair<int, int> &start, const std::pair<int, int> &end);
private:
	const int COST_DIAGONAL = 14;
	const int COST_NONDIAGONAL = 10;
	void sortByLowestF(std::deque<Node> &deque) const;
	int getDiagDistance(const std::pair<int, int> &start, const std::pair<int, int> &end) const;
	int getMovementCost(const std::pair<int, int> &start, const std::pair<int, int> &end) const;
	std::vector<Node> getNeighbors(const Node &node, Map &map);
	bool IsOnList(const Node &node, const std::deque<Node>& list);

};
#endif 