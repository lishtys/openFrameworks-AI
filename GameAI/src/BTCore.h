#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>

class Node
{
public:
	enum class Status
	{
		Invalid,
		Success,
		Failure,
		Running,
	};

	virtual ~Node() {}

	virtual Status update() = 0;
	virtual void initialize() {}
	virtual void terminate(Status s) {}


	Status tick()
	{
		if (status != Status::Running) {
			initialize();
		}

		status = update();

		if (status != Status::Running) {
			terminate(status);
		}

		return status;
	}


	bool isSuccess() const { return status == Status::Success; }
	bool isFailure() const { return status == Status::Failure; }
	bool isRunning() const { return status == Status::Running; }
	bool isTerminated() const { return isSuccess() || isFailure(); }

	void reset() { status = Status::Invalid; }

	using Ptr = std::shared_ptr<Node>;

protected:
	Status status = Status::Invalid;
};


class Composite : public Node
{
public:
	Composite() : it(children.begin()) {}
	virtual ~Composite() {}

	void addChild(Node::Ptr child) { children.push_back(child); }
	bool hasChildren() const { return !children.empty(); }

protected:
	std::vector<Node::Ptr> children;
	std::vector<Node::Ptr>::iterator it;
};


class Decorator : public Node
{
public:
	virtual ~Decorator() {}

	void setChild(Node::Ptr node) { child = node; }
	bool hasChild() const { return child != nullptr; }

protected:
	Node::Ptr child = nullptr;
};


class Blackboard
{
public:
	void setBool(std::string key, bool value) { bools[key] = value; }
	bool getBool(std::string key)
	{
		if (bools.find(key) == bools.end()) {
			bools[key] = false;
		}
		return bools[key];
	}
	bool hasBool(std::string key) const { return bools.find(key) != bools.end(); }

	void setInt(std::string key, int value) { ints[key] = value; }
	int getInt(std::string key)
	{
		if (ints.find(key) == ints.end()) {
			ints[key] = 0;
		}
		return ints[key];
	}
	bool hasInt(std::string key) const { return ints.find(key) != ints.end(); }

	void setFloat(std::string key, float value) { floats[key] = value; }
	float getFloat(std::string key)
	{
		if (floats.find(key) == floats.end()) {
			floats[key] = 0.0f;
		}
		return floats[key];
	}
	bool hasFloat(std::string key) const { return floats.find(key) != floats.end(); }

	void setDouble(std::string key, double value) { doubles[key] = value; }
	double getDouble(std::string key)
	{
		if (doubles.find(key) == doubles.end()) {
			doubles[key] = 0.0f;
		}
		return doubles[key];
	}
	bool hasDouble(std::string key) const { return doubles.find(key) != doubles.end(); }

	void setString(std::string key, std::string value) { strings[key] = value; }
	std::string getString(std::string key)
	{
		if (strings.find(key) == strings.end()) {
			strings[key] = "";
		}
		return strings[key];
	}
	bool hasString(std::string key) const { return strings.find(key) != strings.end(); }

	using Ptr = std::shared_ptr<Blackboard>;

protected:
	std::unordered_map<std::string, bool> bools;
	std::unordered_map<std::string, int> ints;
	std::unordered_map<std::string, float> floats;
	std::unordered_map<std::string, double> doubles;
	std::unordered_map<std::string, std::string> strings;
};


class Leaf : public Node
{
public:
	Leaf() {}
	virtual ~Leaf() {}
	Leaf(Blackboard::Ptr blackboard) : blackboard(blackboard) {}

	virtual Status update() = 0;

protected:
	Blackboard::Ptr blackboard;
};

class BehaviorTree : public Node
{
public:
	BehaviorTree() : blackboard(std::make_shared<Blackboard>()) {}
	BehaviorTree(const Node::Ptr &rootNode) : BehaviorTree() { root = rootNode; }

	Status update() { return root->tick(); }

	void setRoot(const Node::Ptr &node) { root = node; }
	Blackboard::Ptr getBlackboard() const { return blackboard; }

private:
	Node::Ptr root = nullptr;
	Blackboard::Ptr blackboard = nullptr;
};










class Selector : public Composite
{
public:
	void initialize() override
	{
		it = children.begin();
	}

	Status update() override
	{
		assert(hasChildren() && "Composite has no children");

		while (it != children.end()) {
			auto status = (*it)->tick();

			if (status != Status::Failure) {
				return status;
			}

			it++;
		}

		return Status::Failure;
	}
};


class Sequence : public Composite
{
public:
	void initialize() override
	{
		it = children.begin();
	}

	Status update() override
	{
		assert(hasChildren() && "Composite has no children");

		while (it != children.end()) {
			auto status = (*it)->tick();

			if (status != Status::Success) {
				return status;
			}

			it++;
		}

		return Status::Success;
	}
};



class Inverter : public Decorator
{
public:
	Status update() override
	{
		auto s = child->tick();

		if (s == Status::Success) {
			return Status::Failure;
		}
		else if (s == Status::Failure) {
			return Status::Success;
		}

		return s;
	}
};




