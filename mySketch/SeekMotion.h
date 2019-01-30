#pragma once
#include "Boid.h"
#include "DynamicSteering.h"

class SeekMotion
{
public:
	SeekMotion();
	~SeekMotion();


	void Init();

	void Update();


	void Draw();

	void OnMousePressed();

	DynamicArrive arrive;
	DynamicAlign align;

private:

	Boid m_boid;
	Rigidbody targetRigid;
	float timeCnt;

};

