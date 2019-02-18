#pragma once
#include "Graph.h"
#include "ofPolyline.h"

class AStarPathfinding
{
public:
	AStarPathfinding();
	~AStarPathfinding();


	Graph m_map;


	bool found = true;


	void GetPath(int srcX,int srcY,int tarX,int tarY);

	void UpdateChildNodes(const ofPtr<Node>& center, int x, int y);


	std::set<ofPtr<Node>> OpenSet, ClosedSet;
	ofPtr<Node>  srcNode, targetNode;
	std::vector<ofPtr<Node> >  pathList;

	void Draw();
};

