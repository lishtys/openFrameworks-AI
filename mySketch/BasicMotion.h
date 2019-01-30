#pragma once
#include "Boid.h"
#include "Tracking.h"
#include "DynamicSteering.h"
#include "BaseMotion.h"

class BasicMotion 
{
public:
	BasicMotion();
	~BasicMotion();
	void Init() ;
	void Update() ;
	void Draw() ;
	void OnMousePressed();

private:

	Boid m_boid;
	float timeCnt;
	Tracking mTrack;

	
};

