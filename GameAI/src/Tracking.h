#pragma once
#include <vector>
#include "ofVec2f.h"

class Tracking
{
public:
	Tracking();
	~Tracking();


	std::vector<ofVec2f> points;

	void AddBoid(ofVec2f p_f);


};

