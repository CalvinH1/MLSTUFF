#include "Node.h"

void Node::setPrev(Node* prev)
{
	this->prev_ = prev;
}

void Node::setH(int h)
{
	this->heur_ = h;
}

void Node::setG(int g)
{
	this->gcur_ = g;
}

std::pair<int,int> Node::getPosition() const
{
	return this->position_;
}

Node* Node::getPrev() const
{
	return prev_;
}

int Node::getH() const
{
	return heur_;
}

int Node::getG() const
{
	return gcur_;
}

int Node::getF() const
{
	return heur_ + gcur_;
}

bool Node::isTraversable() const
{
	return traversable_;
}

bool Node::operator==(Node node) const
{
	return this->position_ == node.getPosition();
}

Node::Node(std::pair<int, int> position, bool traversable, Node* prev)
{
	this->position_ = position;
	this->prev_ = prev;
	this->traversable_ = traversable;
	heur_ = 0;
	gcur_ = 0;
	func_ = 0;
}

