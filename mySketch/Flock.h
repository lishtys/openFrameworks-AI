#pragma once
#include "ofVec2f.h"
#include "Rigidbody.h"
#include "Boid.h"

class Flock
{
public:
	Flock();
	~Flock();

	std::vector<Boid> boid_list;

	Boid *leader;
	float maxAccerlation;


	ofVec2f GetNeighbourhoodCenter();



};

