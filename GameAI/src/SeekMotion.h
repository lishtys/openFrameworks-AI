#pragma once
#include "Boid.h"
#include "Steering.h"

class SeekMotion
{
public:
	SeekMotion();
	~SeekMotion();


	void Init();
	void Update();
	void Draw();
	void OnMousePressed(int x,int y, int button);

	DynamicArrive arrive;
	DynamicAlign align;

private:

	Boid m_boid;
	Rigidbody targetRigid;
	float timeCnt;

};

