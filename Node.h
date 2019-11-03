#ifndef Node_hpp_
#define Node_hpp_

#include <SFML/Graphics.hpp>
	class Node
	{

	public:

		void setPrev(Node* prev);
		void setH(int heur_);
		void setG(int gcur_);
		std::pair<int,int> getPosition() const;
		Node* getPrev() const;
		int getH() const;
		int getG() const;
		int getF() const;
		bool isTraversable() const;
		bool operator==(Node node) const;
		Node(std::pair<int,int> position, bool traversable, Node* prev);
		
	private:
		Node* prev_;
		std::pair<int,int> position_;
		bool traversable_;
		int heur_;
		int gcur_;
		int func_;
	};

#endif 