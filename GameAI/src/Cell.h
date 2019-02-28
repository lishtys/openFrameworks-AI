#pragma once
#include "ofMathConstants.h"
#include "ofTypes.h"
#include "ofVec2f.h"
#include "ofApp.h"
class Cell;
typedef ofPtr<Cell> NodePtr;

class Cell
{
public:
	Cell();
	~Cell();

	

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
	
	//  Hand Coded
	void SetCost(float cost) { // not walkable < 1 <= walkable
		this->cost = cost;
	}

	void SetEstimate(ofPtr<Cell> & target) {
		int dx = abs(target->pos.x - pos.x);
	    int dy = abs(target->pos.y	 - pos.y);

		switch (ofApp::HeuristicsType)
		{
		case 0:
			this->estimate = dx + dy;
			break;
		case 1:
			this->estimate = max(dx, dy);
			break;
		case 2:
			this->estimate = sqrt(dx * dx + dy * dy);
			break;
		case 3:
			this->estimate = abs(dx - dy) + sqrt(2) * MIN(dx, dy);;
			break;
		case 4:
			float F = sqrt(2) - 1;
			this->estimate=(dx < dy) ? F * dx + dy : F * dy + dx;
			break;
		}

		this->estimate*=ofApp::hWeight;
	}



	bool operator<(const Cell& node) {
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

	ofPtr<Cell>parent;

	ofVec2f pos;
	ofVec2f worldPos;
	float cost = 1;
	float estimate=0, known=0, total=0;

	bool isVisited = false;
};


inline bool operator<(const ofPtr<Cell>& a, const ofPtr<Cell>& b) {
	return (*a) < (*b);
}
