#include "AStarPathfinding.h"



AStarPathfinding::AStarPathfinding()
{
}


AStarPathfinding::~AStarPathfinding()
{
}

void AStarPathfinding::GetPath(int srcX, int srcY, int tarX, int tarY)
{
	found = false;
	OpenSet.clear();
	ClosedSet.clear();

	int width=m_map.width;
	int height=m_map.height;

	srcNode = m_map.GetNode(ofClamp(srcX, 0, width - 1), ofClamp(srcY, 0, height - 1));
	OpenSet.insert(srcNode);	
	
	targetNode = m_map.GetNode(ofClamp(tarX, 0, width - 1), ofClamp(tarY, 0, height - 1));


	//Looking 


	while(!found&&!OpenSet.empty())
	{
		
		auto curNode = *(OpenSet.begin());
		OpenSet.erase(curNode);
		ClosedSet.insert(curNode);

		if(curNode->pos==targetNode->pos)
		{
			//Find
			found = true;
			auto cur = targetNode;
			pathList.clear();
			path.clear();

			while (cur != srcNode) {
				pathList.push_back(cur->pos);
				path.addVertex(cur->pos.x, cur->pos.y);
				cur = cur->parent;
			}
			pathList.push_back(srcNode->pos);
			path.addVertex(srcNode->pos.x, srcNode->pos.y);

		}


		//Neighborhood

		UpdateChildNodes(curNode, -1, -1);
		UpdateChildNodes(curNode, 0, -1);

		UpdateChildNodes(curNode, 1, -1);
		UpdateChildNodes(curNode, -1, 0);
		UpdateChildNodes(curNode, +1, 0);
	
		UpdateChildNodes(curNode, -1, 1);
		UpdateChildNodes(curNode, 0, 1);
		UpdateChildNodes(curNode, 1, 1);
		}

	}

void AStarPathfinding::UpdateChildNodes(const ofPtr<Node>& center, int x, int y)
{
	int width = m_map.width;
	int height = m_map.height;

	x += center->pos.x;
	y += center->pos.y;

	auto valid= x >= 0 && y >= 0 && x < width && y < height;


	if(valid)
	{
		auto node = m_map.GetNode(x, y);

		if(!ClosedSet.count(node)&& node->Walkable())
		{
			auto cost = center->known + center->cost;

			if (OpenSet.count(node)) {
				if (cost < node->known) {
					OpenSet.erase(node);
					node->parent = center;
					node->SetKnown(cost);
					OpenSet.insert(node);
				}
			}
			else
			{
				node->SetEstimate(targetNode);
				node->parent = center;
				node->SetKnown(cost);
				OpenSet.insert(node);
			}
		}

	}
}

void AStarPathfinding::Draw()
{
}


