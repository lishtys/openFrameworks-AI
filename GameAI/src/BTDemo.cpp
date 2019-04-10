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
	auto chaseNode = std::make_shared<ChaseNode>();
	chaseNode->m_monster = &m_monster;
	chaseNode->targetRigid = &m_boid.mRigidbody;
	chaseNode->arrive = &arrive;

	auto seq = std::make_shared<Sequence>();
	seq->addChild(chaseNode);
	tree.setRoot(seq);

	

	
}

void BTDemo::Update()
{
	tree.update();
}
