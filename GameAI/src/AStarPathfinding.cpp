#include "AStarPathfinding.h"
#include "ofGLProgrammableRenderer.h"
#include "ofApp.h"


AStarPathfinding::AStarPathfinding()
{
	
	path_follow.character = &m_boid.mRigidbody;
	path_follow.maxAcceleration = 50;
	path_follow.maxAngularAcc = 10;
	path_follow.maxSpeed = 100;
	path_follow.curIdx = 0;
	mon_boid = NULL;
}


AStarPathfinding::~AStarPathfinding()
{
}

void AStarPathfinding::GetPathForTarget(int tarX,int tarY)
{
	float scaleX = ofGetWidth() / m_map.width;
	float scaleY = ofGetHeight() / m_map.height;
	float mX = tarX;
	float mY =tarY;
	int indexX = mX / scaleX;
	int indexY = mY / scaleY;


	float X = mon_boid->mRigidbody.Position.x;
	float Y = mon_boid->mRigidbody.Position.y;

	int b_indexX = X / scaleX;
	int b_indexY = Y / scaleY;


	{
		targetNode = m_map.GetNode(indexX, indexY);
		srcNode = m_map.GetNode(b_indexX, b_indexY);
	}
	GetPath(30, 30, ofGetMouseX() / 40, ofGetMouseY() / 40);
}

void AStarPathfinding::GetPath(int srcX, int srcY, int tarX, int tarY)
{
	// Graphic Clear
	for (auto mapNode : m_map.NodeList)
	{
		mapNode->isVisited = false;
	}


	// Start of Pathfinding
	found = false;
	OpenSet.clear();
	ClosedSet.clear();


	int width=m_map.width;
	int height=m_map.height;
	
	if(srcNode==nullptr)
	{
		srcNode = m_map.GetNode(ofClamp(srcX, 0, width - 1), ofClamp(srcY, 0, height - 1));
	}
	OpenSet.insert(srcNode);	

	if (targetNode == nullptr)
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

			while (cur != srcNode) {
				pathList.push_back(cur);
				cur = cur->parent;
			}
			pathList.push_back(srcNode);

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


	
	
	path_follow.curIdx = 0;


}

void AStarPathfinding::RunBoid()
{


	path_follow.pRadius = 20;
	path_follow.path = pathList;
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;

	path_follow.getSteering(&steer);

	m_boid.Update(steer, deltaTime);

	m_boid.mRigidbody.LookToMovment();

}

void AStarPathfinding::UpdateChildNodes(const ofPtr<Cell>& center, int x, int y)
{
	int width = m_map.width;
	int height = m_map.height;

	int nx = x;
	int ny = y;

	x += center->pos.x;
	y += center->pos.y;

	auto valid= x >= 0 && y >= 0 && x < width && y < height;


	if(valid)
	{
		auto node = m_map.GetNode(x, y);
		node->isVisited = true;
		if(!ClosedSet.count(node)&& node->Walkable())
		{
			auto cost = center->known+1;
			if (!(nx == 0 || ny == 0)) cost += sqrt(2) - 1;


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
	float scaleX = ofGetWidth() / m_map.width;
	float scaleY = ofGetHeight() / m_map.height;




	for (auto mapNode : m_map.NodeList)
	{

		// if (mapNode->isVisited)
		// {
		// 	ofSetColor(ofColor::cadetBlue);
		// 	ofDrawRectangle(mapNode->pos.x*scaleX, mapNode->pos.y *scaleY, scaleX, scaleY);
		// }


		if(ofApp::showUnwalkableNode)
		{
			if (mapNode->cost == 0)
			{
				ofSetColor(ofColor::black);
				ofDrawRectangle(mapNode->pos.x*scaleX, mapNode->pos.y *scaleY, scaleX, scaleY);
			}
		}
	
	}





	for (auto pathNode : pathList)
	{
		int x = pathNode->pos.x;
		int y = pathNode->pos.y;

		
		ofSetColor(ofColor::red);
		ofDrawRectangle(x*scaleX, y *scaleY, scaleX, scaleY);
	}


	// highlight
    float mX=ofGetMouseX();
    float mY=ofGetMouseY();

	int indexX = mX / scaleX;
	int indexY = mY / scaleY;

	ofSetColor(ofColor::yellow);
	ofDrawRectangle((indexX)*scaleX, indexY*scaleY, scaleX, scaleY);

	// SrcNode

	if(srcNode!=nullptr)
	{
		ofSetColor(ofColor::green);
		ofDrawRectangle(srcNode->pos.x*scaleX, srcNode->pos.y*scaleY, 10,10);
	}
	
	if(targetNode !=nullptr)
	{
		ofSetColor(ofColor::blue);
		ofDrawRectangle(targetNode->pos.x*scaleX, targetNode->pos.y*scaleY, 10, 10);
	}

	if(ofApp::needBoid)
	{
		//boid
		m_boid.Draw();
		ofSetColor(0, 255, 0);
	}
	



}

void AStarPathfinding::OnKeyReleased(int key)
{
	if (key == 'r')
	{
		GetPath(30, 30, ofGetMouseX() / 40, ofGetMouseY() / 40);
	}

	if (key == 'z')
	{
		isAddingWall = false;
	}
}

void AStarPathfinding::OnKeyPressed(int key)
{
	if (key == 'z')
	{
		isAddingWall = true;
	}
}

void AStarPathfinding::OnMousePressed(int x, int y, int button)
{
	float scaleX = ofGetWidth() / m_map.width;
	float scaleY = ofGetHeight() / m_map.height;

	if(button==0)
	{
		float mX = ofGetMouseX();
		float mY = ofGetMouseY();
		int indexX = mX / scaleX;
		int indexY = mY / scaleY;

		if(!isAddingWall)
		{
			// highlight
			
			srcNode = m_map.GetNode(indexX, indexY);
		}
		else
		{
			auto node = m_map.GetNode(indexX, indexY);
			node->SetCost(0);

		}


	}
	else
	{
		// highlight
		float mX = ofGetMouseX();
		float mY = ofGetMouseY();
		int indexX = mX / scaleX;
		int indexY = mY / scaleY;
		targetNode = m_map.GetNode(indexX, indexY);
	}
	

}

void AStarPathfinding::OnMouseClick(int x, int y, int button)
{
	if (button == 0)
	{
		float scaleX = ofGetWidth() / m_map.width;
		float scaleY = ofGetHeight() / m_map.height;
		float mX = ofGetMouseX();
		float mY = ofGetMouseY();
		int indexX = mX / scaleX;
		int indexY = mY / scaleY;


		float X = m_boid.mRigidbody.Position.x;
		float Y = m_boid.mRigidbody.Position.y;

		int b_indexX = X / scaleX;
		int b_indexY = Y / scaleY;

		if (ofApp::needBoid)
		{
			targetNode = m_map.GetNode(indexX, indexY);
			srcNode = m_map.GetNode(b_indexX, b_indexY);
		}
		GetPath(30, 30, ofGetMouseX() / 40, ofGetMouseY() / 40);
	}
	
}


