#include "BTDemo.h"
#include "ofBitmapFont.h"


BTDemo::BTDemo()
{
}


BTDemo::~BTDemo()
{
}

void BTDemo::Draw()
{
	m_boid.Draw();
	m_monster.Draw();
	// ofSetColor(0, 255, 0);
	// ofDrawBitmapString(m_boid.mRigidbody.Velocity, 100, 100);
}

void BTDemo::Init()
{

	m_boid.mRigidbody.Position.x = ofRandomWidth();
	m_boid.mRigidbody.Position.y = ofRandomHeight();
	m_monster.mRigidbody.Position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	
	
	
	arrive.character = &m_monster.mRigidbody;
	arrive.targetBoid = &m_boid.mRigidbody;
	arrive.maxAcceleration = 50;
	arrive.maxAngularAcc = 10;
	arrive.maxSpeed = 100;

	arrive.TargetRadius = 5;
	arrive.slowRadius = 200;
	arrive.timeToTarget = 5;;



	// Nodes Initialization 
	 
	chase_node = std::make_shared<ChaseNode>();
	chase_node->m_monster = &m_monster;
	chase_node->targetRigid = &m_boid.mRigidbody;
	chase_node->arrive = &arrive;

	auto seq = std::make_shared<Sequence>();
	seq->addChild(chase_node);
	tree.setRoot(seq);

	

	
}

void BTDemo::Update()
{
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;
	chase_node->steer = &steer;

	tree.update();

	m_monster.Update(steer, deltaTime);

	m_monster.mRigidbody.LookToMovment();
}
