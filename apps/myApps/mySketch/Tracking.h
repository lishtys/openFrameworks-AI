#pragma once
#include <vector>
#include "Boid.h"

class Tracking
{
public:
	Tracking();
	~Tracking();


	std::vector<Boid> boid_list;

	void AddBoid(Boid boid);


	void Draw();
};

