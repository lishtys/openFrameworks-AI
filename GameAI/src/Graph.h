#pragma once
#include <set>
#include "Node.h"
#include "ofPixels.h"


class Graph
{
public:
	Graph();
	~Graph();


	void Setup(ofPixels& pix);
	void Setup(int col,int row);

	void DarwNodes();

	ofPtr<Node>& GetNode(int x, int y);
	
	std::vector<ofPtr<Node>> NodeList;

	float width;
	float height;
};

