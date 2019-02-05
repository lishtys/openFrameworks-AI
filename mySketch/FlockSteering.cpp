#include "FlockSteering.h"
#include "of3dPrimitives.h"


FlockSteering::FlockSteering()
{
	
}


FlockSteering::~FlockSteering()
{
	
}



void DynamicSeparation::getSteering(SteeringOutput* output)
{
	// auto boid_list = mFlock->boid_list;
	// auto leader = mFlock->leader;
	//
	// ofVec2f targetVel={0,0};
	//
	//
	//
	// for (auto element : boid_list)
	// {
	// 	auto diff = mCharacter->mRigidbody.Position - element.mRigidbody.Position  ;
	// 	auto distance = diff.length();
	// 	if (&element != mCharacter && distance < sepDistance) {
	// 		diff = diff / distance;
	// 		targetVel= targetVel-(diff);
	// 	}
	// }
	// output->linear = targetVel*20;
	// if(targetVel.length()> maxAcc)
	// output->linear = targetVel.getNormalized()*maxAcc;



	auto boid_list = mFlock->boid_list;
	auto leader = mFlock->leader;
	auto maxAccerlation = mFlock->maxAccerlation;
	
	for (auto element : boid_list)
	{
	
		auto direction =  mCharacter->mRigidbody.Position- element.mRigidbody.Position;
		auto distance = direction.length();
	
		if (distance < sepDistance&& distance>0.0001f)
		{
			auto strength = 10000* 1/ (distance * distance) ;
			output->linear += strength * direction.normalize();
		}
		
	}
}


void DynamicMatchVel::getSteering(SteeringOutput* output)
{


	auto boid_list = mFlock->boid_list;

	ofVec2f targetVel = { 0,0 };
	int cnt = 0;
	for (auto element : boid_list)
	{
		auto diff = element.mRigidbody.Position - mCharacter->mRigidbody.Position;
		auto distance = diff.length();
		if (&element != mCharacter && distance < radius) {
			targetVel += element.mRigidbody.Velocity;
			cnt++;
		}
	}

	targetVel = targetVel / cnt;
	targetVel = targetVel- mCharacter->mRigidbody.Velocity;
	
	output->linear = targetVel;

	if (targetVel.length() > mFlock->maxAccerlation)

		output->linear = targetVel.getNormalized()*mFlock->maxAccerlation;
	
	}

void KinematicSeparation::getSteering(SteeringOutput* output)
{

	auto boid_list = mFlock->boid_list;
	auto leader = mFlock->leader;
	ofVec2f targetPos;
	
	for (auto element : boid_list)
	{
		auto diff = element.mRigidbody.Position - mCharacter->mRigidbody.Position;
		auto distance = diff.length();
		if (&element != mCharacter  && distance < sepDistance) {
			diff = diff.getNormalized();
			diff /= distance;
			output->Velocity+=(diff); 
		}
	}

	output->Velocity=output->Velocity.getNormalized()*maxSpeed;

}

void KinematicAvoid::getSteering(SteeringOutput* output)
{

	auto boid_list = mFlock->boid_list;
	auto leader = mFlock->leader;
	ofVec2f targetPos;


	// for (auto element : boid_list)
	// {
	// 	auto diff = element.mRigidbody.Position - mCharacter->mRigidbody.Position;
	// 	auto distance = diff.length();
	// 	if (&element != mCharacter && distance < sepDistance) {
	// 		diff = diff.getNormalized();
	// 		diff /= distance;
	// 		output->Velocity += (diff);
	// 	}
	// }

	output->Velocity = output->Velocity.getNormalized()*maxSpeed;
	// for (int i = 0; i < objs.size(); i++) {
	// 	Obj obj = (Obj)objs.get(i);
	// 	// Distance between object and avoidance sphere
	// 	float distance = dist2(obj.pos, pos);
	// 	// If distance is less than the sum of the two radius, there is collision
	// 	float bound = obj.mass*0.5f + BRadius + ORadius;
	// 	if (distance < bound*bound) {
	// 		wAvo = 10.0f;
	// 		wWan = 0.1f;
	// 		float collision = (obj.mass + mass)*0.5f;
	// 		if (distance < collision*collision) {
	// 			steer = PVector.sub(pos, obj.pos);
	// 			steer.mult(maxforce*0.1f);
	// 			return steer;
	// 		}
	// 		else {
	// 			float direction = dist2(obj.pos, PVector.add(pos, vel));
	// 			// If is heading toward obstacle
	// 			if (direction < distance) {
	// 				// If steering in the verticle direction
	// 				if (abs(vel.x) <= abs(vel.y)) {
	// 					steer = new PVector((pos.x - obj.pos.x), vel.y);
	// 					steer.mult(maxforce*((bound*bound) / distance)*0.001f);
	// 				}
	// 				// If steering in the horizontal direction
	// 				else {
	// 					steer = new PVector(vel.x, (pos.y - obj.pos.y));
	// 					steer.mult(maxforce*((bound*bound) / distance)*0.001f);
	// 				}
	// 			}
	// 		}
	// 	}
	// }
}



