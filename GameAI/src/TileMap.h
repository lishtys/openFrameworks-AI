#pragma once
#include <set>
#include "Cell.h"
#include "ofPixels.h"


class TileMap
{
public:
	TileMap();
	~TileMap();


	void Setup(ofPixels& pix);
	void Setup(int col,int row);

	void DarwNodes();

	ofPtr<Cell>& GetNode(int x, int y);
	
	std::vector<ofPtr<Cell>> NodeList;

	float width;
	float height;
};

