#pragma once
#include "Boid.h"
#include "Tracking.h"

class BasicMotion
{
public:
	BasicMotion();
	~BasicMotion();
	void Init();
	void Update();
	void Draw();
	void Rotate(float rad);

private:

	Boid m_boid;
	float timeCnt;
	Tracking mTrack;
};

