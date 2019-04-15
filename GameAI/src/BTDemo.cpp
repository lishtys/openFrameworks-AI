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
	
	// a_pathfinding.m_map.DarwNodes();
	// a_pathfinding.Draw();
	// cur_img->draw(0, 0, 1920, 1080);
	m_boid.Draw();
	m_monster.Draw();



	// ofSetColor(0, 255, 0);
	// ofDrawBitmapString(m_boid.mRigidbody.Velocity, 100, 100);
}

void BTDemo::Init()
{

	a_pathfinding.pathList.clear();
	a_pathfinding.srcNode = nullptr;
	a_pathfinding.targetNode = nullptr;
	img_node.loadImage("SimpleNode.png");
	cur_img = &img_node;

	a_pathfinding.m_map.Setup(*cur_img);

	m_boid.mRigidbody.Position.x = ofRandomWidth();
	m_boid.mRigidbody.Position.y = ofRandomHeight();
	
	
	m_monster.mRigidbody.Position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	m_monster.mColor= { 255,0,0 };




	targetRigid.Position= ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

	
	arrive.character = &m_monster.mRigidbody;
	arrive.targetBoid = &m_boid.mRigidbody;
	arrive.maxAcceleration = 50;
	arrive.maxAngularAcc = 10;
	arrive.maxSpeed = 100;

	arrive.TargetRadius = 5;
	arrive.slowRadius = 200;
	arrive.timeToTarget = 5;;

	// Dynamic
	wander.character = &m_boid.mRigidbody;
	wander.targetBoid = &targetRigid;

	// Nodes Initialization 
	 
	chase_node = std::make_shared<ChaseNode>();
	wander_node = std::make_shared<WanderNode>();
	check_near_node = std::make_shared<CheckNearNode>();
	respawn_node = std::make_shared<RespawnNode>();

	chase_node->m_monster = &m_monster;
	chase_node->targetRigid = &m_boid.mRigidbody;
	chase_node->arrive = &arrive;


	wander_node->m_monster = &m_monster;
	wander_node->targetRigid = &m_boid.mRigidbody;
	wander_node->wander = &wander;

	
	check_near_node->m_monster = &m_monster;
	check_near_node->m_boid = &m_boid;


	respawn_node->m_monster = &m_monster;
	respawn_node->m_boid = &m_boid;

	auto select= std::make_shared<Selector>();
	auto seq1 = std::make_shared<Sequence>();
	seq1->addChild(check_near_node);
	seq1->addChild(respawn_node);
	select->addChild(seq1);

	//
	auto seq2 = std::make_shared<Sequence>();
	seq2->addChild(chase_node);
	select->addChild(seq2);
	//
	mon_tree.setRoot(select);



	auto seq = std::make_shared<Sequence>();
	boid_tree.setRoot(seq);
	auto invert=std::make_shared<Inverter>();
	invert->setChild(check_near_node);
	seq->addChild(invert);
	// seq->addChild(wander_node);

	
}

void BTDemo::Update()
{

	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;
	SteeringOutput mon_steer;
	// a_pathfinding.GetPath(0, 0, 0, 0);
	
	
	wander_node->steer = &steer;
	chase_node->steer = &mon_steer;

	boid_tree.update();
	 mon_tree.update();
	
	m_boid.Update(steer,deltaTime);

    m_monster.Update(mon_steer, deltaTime);

	m_monster.mRigidbody.LookToMovment();
	m_boid.mRigidbody.LookToMovment();
}
