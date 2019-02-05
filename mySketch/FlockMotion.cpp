#include "FlockMotion.h"
#include <ofAppGlutWindow.h>
#include "of3dPrimitives.h"
#include "ofBitmapFont.h"
#include "ofApp.h"


FlockMotion::FlockMotion()
{
}


FlockMotion::~FlockMotion()
{
}

void FlockMotion::Init()
{
	flock.boid_list.clear();
	avoid.boids.clear();
	obstacles_list.clear();


	for (unsigned i = 0; i < 20; i++)
	{
		Boid boid;
		boid.mRigidbody.Position.x = ofRandomWidth();
		boid.mRigidbody.Position.y = ofRandomHeight();
		boid.mRigidbody.Orientation = ofRandomf() * 2 * 3.141592;
		boid.mRigidbody.Velocity.x = ofRandomf() * 4;
		boid.mRigidbody.Velocity.y = ofRandomf() * 4;
		boid.mRigidbody.Rotation = 0;
		flock.boid_list.push_back(boid);
	
		avoid.boids.push_back(&flock.boid_list[i]);
	}

	




	for (unsigned i = 0; i < 3; i++)
	{
		Obstacle obj;
		obj.mRigidbody.Position.x = ofRandomWidth();
		obj.mRigidbody.Position.y = ofRandomHeight();
		obstacles_list.push_back(obj);
		
	}




	flock.maxAccerlation = 10;

	d_separation.mFlock = &flock;
	d_separation.sepDistance = 100;
	d_separation.maxAcc = 20;
	
	
	// k_separation.mFlock = &flock;
	// k_separation.sepDistance = 40;

	d_velMatch.mFlock = &flock;




}

void FlockMotion::Update()
{
	

	// Flock Seek
	targetRigid.Position= flock.GetNeighbourhoodCenter();
	if (flock.leader != nullptr)
		targetRigid = flock.leader->mRigidbody;
	
	if (flock.leaderB != nullptr)
		targetRigidB = flock.leaderB->mRigidbody;

	d_seek.targetBoid = &targetRigid;
	d_align.targetBoid = &targetRigid;

	for (unsigned i = 0; i < flock.boid_list.size(); i++)
	{

		SteeringOutput seek_output;
		SteeringOutput align_output;
		SteeringOutput avoid_output;
		SteeringOutput sep_output;
		SteeringOutput vel_output;
		SteeringOutput wander_output;

		if (flock.leaderB == nullptr &&flock.leader == nullptr)
		{
			d_seek.targetBoid = &targetRigid;
			d_align.targetBoid = &targetRigid;
		}
		else if(flock.leaderB != nullptr&&flock.leader == nullptr)
		{
			d_seek.targetBoid = &targetRigidB;
			d_align.targetBoid = &targetRigidB;
		}
		else if(flock.leaderB != nullptr &&flock.leader != nullptr)
		{
			auto bDis = (flock.leaderB->mRigidbody.Position - flock.boid_list[i].mRigidbody.Position).length();
			auto aDis = (flock.leader->mRigidbody.Position - flock.boid_list[i].mRigidbody.Position).length();

			if(bDis<aDis)
			{
				d_seek.targetBoid = &targetRigidB;
				d_align.targetBoid = &targetRigidB;
			}else
			{
				d_seek.targetBoid = &targetRigid;
				d_align.targetBoid = &targetRigid;
			}
		}


		

		if(&flock.boid_list[i]!= flock.leader && &flock.boid_list[i] != flock.leaderB)
		{
			 d_seek.character = &flock.boid_list[i].mRigidbody;
			 d_align.character = &flock.boid_list[i].mRigidbody;
			 d_seek.getSteering(&seek_output);
		}

		else
		{
			// Leader Wander
			if (flock.leader != nullptr || flock.leaderB != nullptr)
			{
				d_wander.character = &flock.boid_list[i].mRigidbody;
				d_wander.getSteering(&wander_output);
				flock.boid_list[i].Update(wander_output, ofGetLastFrameTime());
				flock.boid_list[i].mRigidbody.LookToMovment();
				continue;
			}
		

		}


		//Avoid Collision

		{
			avoid.character = &flock.boid_list[i].mRigidbody;
			avoid.characterRadius = flock.boid_list[i].CircleRadius;
			avoid.elements = obstacles_list;
			avoid.getSteering(&avoid_output);
		}


		d_velMatch.mCharacter = &flock.boid_list[i];
		d_velMatch.getSteering(&vel_output);



		d_separation.mCharacter = &flock.boid_list[i];
		d_separation.getSteering(&sep_output);



		d_wander.character = &flock.boid_list[i].mRigidbody;
		d_wander.getSteering(&wander_output);

		targetRigid.Orientation = d_align.character->GetMovementOrientation();
		d_align.getSteering(&align_output);


		SteeringOutput steering_output;

		steering_output.linear += seek_output.linear* (flock.boid_list[i].mRigidbody.wSeek) ;
		 steering_output.linear += avoid_output.linear*(flock.boid_list[i].mRigidbody.wAvo) ;
		steering_output.linear += sep_output.linear*(flock.boid_list[i].mRigidbody.wSep) ;
		 steering_output.linear += wander_output.linear*(flock.boid_list[i].mRigidbody.wWan) ;
		 steering_output.linear += vel_output.linear*(flock.boid_list[i].mRigidbody.wVel) ;
		steering_output.angular += align_output.angular ;

		flock.boid_list[i].Update(steering_output, ofGetLastFrameTime());
	}






	


}

void FlockMotion::Draw()
{
	for (unsigned i = 0; i < flock.boid_list.size(); i++)
	{
		flock.boid_list[i].Draw();
	}

	for (unsigned i = 0; i < 3; i++)
	{
		obstacles_list[i].Draw();
	}

	
}

void FlockMotion::OnMousePressed(int x, int y,int button )
{
	for (unsigned i = 0; i < flock.boid_list.size(); i++)
	{
		auto boid = &flock.boid_list[i];
		auto pos= flock.boid_list[i].mRigidbody.Position;
		float dist = ofDist(pos.x, pos.y,x , y);
		 if (dist < boid->CircleRadius)
		{
			 if(button==0)
			 {
				 if (flock.leader != nullptr) flock.leader->mColor = { 0,0,0 };
				 flock.leader = boid;  boid->mColor = { 255,0,0 };
				 targetRigid = flock.leader->mRigidbody;
			 }else
			 {
				 if (flock.leaderB != nullptr) flock.leaderB->mColor = { 0,0,0 };
				 flock.leaderB = boid;  boid->mColor = { 0,255,0 };
				 targetRigidB = flock.leaderB->mRigidbody;
			 }
			
		}
	}

	
}
