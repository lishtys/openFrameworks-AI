#pragma once
#include "TileMap.h"
#include "ofPolyline.h"
#include "Boid.h"
#include "Steering.h"

class AStarPathfinding
{
public:
	AStarPathfinding();
	~AStarPathfinding();


	TileMap m_map;


	bool found = true;


	void GetPath(int srcX,int srcY,int tarX,int tarY);

	void RunBoid();

	void UpdateChildNodes(const ofPtr<Cell>& center, int x, int y);


	std::set<ofPtr<Cell>> OpenSet, ClosedSet;
	ofPtr<Cell>  srcNode, targetNode;
	std::vector<ofPtr<Cell> >  pathList;

	void Draw();

	void OnKeyReleased(int key);
	void OnKeyPressed(int key);

	void OnMousePressed(int x, int y, int button);
	void OnMouseClick(int x, int y, int button);



	// Pathfollowing
	Boid m_boid;
	Follow path_follow;


	//Ctrl Flag

	bool isAddingWall;

};

