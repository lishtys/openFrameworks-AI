#pragma once
#include "ofMathConstants.h"
#include "ofTypes.h"
#include "ofVec2f.h"
class Node;
typedef ofPtr<Node> NodePtr;

class Node
{
public:
	Node();
	~Node();

	

	void getNeighbor(int& x, int& y) const {
		x += this->pos.x, y += this->pos.y;
	}
	bool Walkable() const {
		return cost >= 1;
	}

	void SetKnown(float known) {
		this->known = known;
		total = known + estimate;
	}
	void SetCost(float cost) { // not walkable < 1 <= walkable
		this->cost = cost;
	}

	void SetEstimate(ofPtr<Node> & target) {
		int dx = abs(target->pos.x - pos.x);
	    int dy = abs(target->pos.y	 - pos.y);
		this->estimate = abs(dx - dy) + sqrt(2) * MIN(dx, dy);
	}



	bool operator<(const Node& node) {
		if (total < node.total) {
			return true;
		}
		else if (total > node.total) {
			return false;
		}
		if (pos.x < node.pos.x) {
			return true;
		}
		else if (pos.x > node.pos.x) {
			return false;
		}
		else {
			return (pos.y < node.pos.y);
		}
	}

	ofPtr<Node>parent;

	ofVec2f pos;
	float cost = 1;
	float estimate=0, known=0, total=0;
};


inline bool operator<(const ofPtr<Node>& a, const ofPtr<Node>& b) {
	return (*a) < (*b);
}
