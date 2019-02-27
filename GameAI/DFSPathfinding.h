#include "TileMap.h"
#include "ofPolyline.h"

#pragma once
class DFSPathfinding
{
public:
	DFSPathfinding();
	~DFSPathfinding();


	TileMap m_map;

	bool found = true;


	void GetPath(int srcX, int srcY, int tarX, int tarY);

	void UpdateChildNodes(const ofPtr<Cell>& center, int x, int y);


	std::set<ofPtr<Cell>> OpenSet, ClosedSet;
	ofPtr<Cell>  srcNode, targetNode;
	std::vector<ofPtr<Cell> >  pathList;

	void Draw();

	void OnKeyReleased(int key);

	void OnMousePressed(int x, int y, int button);
};

