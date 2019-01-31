#pragma once
#include "Flock.h"
#include "SteeringOutput.h"
#include "FlockSteering.h"
#include "KinematicSteering.h"

class FlockMotion
{
public:
	FlockMotion();
	~FlockMotion();

	void Init();
	void Update();
	void Draw();
	void OnMousePressed(int x,int y);

	Flock flock;


	DynamicSeparation d_separation;
	KinematicSeparation k_separation;


	DynamicSeek d_seek;
	DynamicAlign d_align;
	DynamicWander d_wander;
	DynamicMatchVel d_velMatch;
	
	std::vector<Avoid> avoid_list;
	std::vector<Obstacle> obstacles_list;

	Boid leader;
	Rigidbody	 targetRigid;






};

