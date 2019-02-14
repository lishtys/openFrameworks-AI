#pragma once
#include "Flock.h"
#include "SteeringOutput.h"
#include "FlockSteering.h"
#include "Steering.h"

class FlockMotion
{
public:
	FlockMotion();
	~FlockMotion();

	void Init();
	void Update();
	void Draw();
	void OnMousePressed(int x,int y,int button);

	Flock flock;


	DynamicSeparation d_separation;
	KinematicSeparation k_separation;


	DynamicSeek d_seek;
	DynamicAlign d_align;
	DynamicWander d_wander;
	DynamicMatchVel d_velMatch;
	
	Avoid avoid;
	std::vector<Obstacle> obstacles_list;

	Boid leader;
	Boid leaderB;
	Rigidbody	 targetRigid;
	Rigidbody	 targetRigidB;






};

