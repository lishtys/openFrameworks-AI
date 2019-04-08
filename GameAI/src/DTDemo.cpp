#include "DTDemo.h"


bool BoidWallDecisionNode::GetBranch()
{
	auto Position = m_boid->mRigidbody.Position;
	auto maxX = ofGetWidth();
	auto maxY = ofGetHeight();
	auto minX = 0;
	auto minY = 0;

	int detectionRange = 20;

	if (Position.x < minX+ detectionRange) {
		return true;
	}
	if (Position.x > maxX- detectionRange) {
		return true;
	}
	if (Position.y < minY+detectionRange) {
		return true;
	}
	if (Position.y > maxY-detectionRange) {
		return true;
	}

	return false;
}

bool BoidTargetDecisionNode::GetBranch()
{
	auto Position = m_boid->mRigidbody.Position;
	auto speed = m_boid->mRigidbody.Velocity.lengthSquared();
	auto targetPos = targetRigid->Position;
	
	auto dist=Position.distanceSquared(targetPos);

	if (dist < 20) return true;
	return false;
	
}

void BoidTargetActionNode::DoAction()
{
	targetRigid->Position.x = ofRandomWidth();
	targetRigid->Position.y = ofRandomHeight();
}

void BoidWallActionNode::DoAction()
{
	targetRigid->Position.x = ofRandomWidth()/2;
	targetRigid->Position.y = ofRandomHeight()/2;
}

void BoidArriveActionNode::DoAction()
{
	auto deltaTime = ofGetLastFrameTime();
	arrive->getSteering(steer);
	
}

DTDemo::DTDemo()
{
}


DTDemo::~DTDemo()
{
}

void DTDemo::Draw()
{
	m_boid.Draw();
	ofSetColor(0, 255, 0);
	ofDrawCircle(targetRigid.Position.x, targetRigid.Position.y, 10);
	ofDrawBitmapString(m_boid.mRigidbody.Velocity, 100, 100);
}

void DTDemo::Init()
{

	RandomPosition();
	m_boid.mRigidbody.Position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	arrive.character = &m_boid.mRigidbody;
	arrive.targetBoid = &targetRigid;
	arrive.maxAcceleration = 50;
	arrive.maxAngularAcc = 10;
	arrive.maxSpeed = 100;

	arrive.TargetRadius = 5;
	arrive.slowRadius = 200;
	arrive.timeToTarget = 5;;




	

	// DT Initialization 
	wall_dec_node.m_boid = &m_boid;
	wall_dec_node.targetRigid = &targetRigid;

	target_dec_node.m_boid = &m_boid;
	target_dec_node.targetRigid = &targetRigid;

	wall_action_node.m_boid = &m_boid;
	wall_action_node.targetRigid = &targetRigid;	
	
	target_action_node.m_boid = &m_boid;
	target_action_node.targetRigid = &targetRigid;
	
	arrive_action_node.m_boid = &m_boid;
	arrive_action_node.targetRigid = &targetRigid;	
	
	arrive_action_node.arrive = &arrive;
	



	//SetUp
	wall_dec_node.trueBranch = &wall_action_node;
	wall_dec_node.falseBranch = &target_dec_node;


	target_dec_node.trueBranch = &target_action_node;
	target_dec_node.falseBranch = &arrive_action_node;

}

void DTDemo::Update()
{
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;
	arrive_action_node.steer = &steer;

    DecisionTreeNode *node = wall_dec_node.MakeDecision();

	auto   actionNode= dynamic_cast<DecisionTreeAction*>(node);
	actionNode->DoAction();
	
	m_boid.Update(steer, deltaTime);

	m_boid.mRigidbody.LookToMovment();
}

void DTDemo::RandomPosition()
{

	targetRigid.Position.x = ofRandomWidth();
	targetRigid.Position.y = ofRandomHeight();

}
