#pragma once
#include "Boid.h"
#include "Steering.h"

class BasicMotion 
{
public:
	BasicMotion();
	~BasicMotion();
	 void Init();
	 void Update() ;
	 void Draw() ;
	 void OnMousePressed(int x,int y,int button);

private:

	Boid m_boid;
	float timeCnt;

	
};

