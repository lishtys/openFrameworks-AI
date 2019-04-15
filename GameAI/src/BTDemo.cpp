#include "BTDemo.h"
#include "ofBitmapFont.h"








bool BoidTDecisionNode::GetBranch()
{
	auto Position = m_boid->mRigidbody.Position;
	auto speed = m_boid->mRigidbody.Velocity.lengthSquared();
	auto targetPos = targetRigid->Position;

	auto dist = Position.distanceSquared(targetPos);

	if (dist < 20) return true;
	return false;
}

void BoidTActionNode::DoAction()
{
	targetRigid->Position.x = ofRandomWidth();
	targetRigid->Position.y = ofRandomHeight();
}



void BoidChasActionNode::DoAction()
{
	pathfinding->path_follow.character = &mon_boid->mRigidbody;
	pathfinding->path_follow.pRadius = 20;
	pathfinding->path_follow.path = pathfinding->pathList;
	pathfinding->path_follow.getSteering(steer);
}

BTDemo::BTDemo()
{
}


BTDemo::~BTDemo()
{
}

void BTDemo::Draw()
{
	
	// a_pathfinding.m_map.DarwNodes();
	 ofSetColor(255, 255, 255);
	 cur_img->draw(0, 0, 1920, 1080);
	m_boid.Draw();
	m_monster.Draw();
	learn_monster.Draw();
	a_pathfinding.Draw();
	learn_pathfinding.Draw();



	// ofSetColor(0, 255, 0);
	// ofDrawBitmapString(m_boid.mRigidbody.Velocity, 100, 100);
}

void BTDemo::Init()
{

	a_pathfinding.pathList.clear();
	a_pathfinding.srcNode = nullptr;
	a_pathfinding.targetNode = nullptr;
	img_node.loadImage("maze.png");
	cur_img = &img_node;

	a_pathfinding.m_map.Setup(*cur_img);
	a_pathfinding.mon_boid = &m_monster;




	learn_pathfinding.pathList.clear();
	learn_pathfinding.srcNode = nullptr;
	learn_pathfinding.targetNode = nullptr;
	

	learn_pathfinding.m_map.Setup(*cur_img);
	learn_pathfinding.mon_boid = &learn_monster;
	learn_pathfinding.path_follow.character= &learn_monster.mRigidbody;


	// m_boid.mRigidbody.Position.x = ofRandomWidth();
	// m_boid.mRigidbody.Position.y = ofRandomHeight();
	
	
	m_monster.mRigidbody.Position = ofVec2f(400.0, 550.0);
	m_boid.mRigidbody.Position = ofVec2f(1200, 550.0);
	learn_monster.mRigidbody.Position = ofVec2f(1600, 800.0);

	m_monster.mColor= { 255,0,0 };
	learn_monster.mColor= { 0,255,0 };




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
	chase_node->a_star_pathfinding = &a_pathfinding;


	wander_node->m_monster = &m_monster;
	wander_node->targetRigid = &m_boid.mRigidbody;
	wander_node->wander = &wander;

	
	check_near_node->m_monster = &m_monster;
	check_near_node->m_boid = &m_boid;


	respawn_node->m_monster = &m_monster;
	respawn_node->m_boid = &m_boid;
	respawn_node->a_pathfinding = &a_pathfinding;

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


	a_pathfinding.GetPathForTarget(m_boid.mRigidbody.Position.x, m_boid.mRigidbody.Position.y);
	learn_pathfinding.GetPathForTarget(m_boid.mRigidbody.Position.x, m_boid.mRigidbody.Position.y);






	// DT Learning 



	target_dec_node.m_boid = &m_boid;
	target_dec_node.targetRigid = &targetRigid;



	target_action_node.m_boid = &m_boid;
	target_action_node.targetRigid = &targetRigid;

	chase_action_node.mon_boid = &learn_monster;
	chase_action_node.pathfinding = &learn_pathfinding;




	//SetUp

	target_dec_node.trueBranch = &target_action_node;
	target_dec_node.falseBranch = &chase_action_node;




}

void BTDemo::Update()
{

	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;
	SteeringOutput mon_steer;
	SteeringOutput learn_steer;

	
	wander_node->steer = &steer;
	chase_node->steer = &mon_steer;
	chase_action_node.steer = &learn_steer;

	boid_tree.update();
	mon_tree.update();

	DecisionTreeNode *node = target_dec_node.MakeDecision();
	auto   actionNode = dynamic_cast<DecisionTreeAction*>(node);
	actionNode->DoAction();


	learn_monster.Update(learn_steer, deltaTime);
	m_boid.Update(steer,deltaTime);
    m_monster.Update(mon_steer, deltaTime);

	m_monster.mRigidbody.LookToMovment();
	m_boid.mRigidbody.LookToMovment();
	learn_monster.mRigidbody.LookToMovment();
}
