#include "Action.h"
#include <cstddef>


Action::Action()
{
}


Action::~Action()
{
}

Action* Action::GetLast()
{
	// If we're at the end, then end
	if (next == NULL) return this;

	// Otherwise find the end iteratively
	Action* thisAction = this;
	Action* nextAction = next;
	while (nextAction) {
		thisAction = nextAction;
		nextAction = nextAction->next;
	}

	// The final element is in thisAction, so return it
	return thisAction;
}

void ActionManager::RunActive()
{
	Action ** previous = &active;
	Action * next = active;

	while (next != NULL)
	{
		// Do the action first
		

		// Check if we're done with this action
		if (true)
		{
			// Remove it from the list
			*previous = next->next;

			// Keep a temp of what we're about to delete
			Action * temp = next;

			// Move the next pointer only along (previous stays)
			next = next->next;

			// And delete the item
			delete temp;
		}
		else
		{
			// We're not done, just chug along
			previous = &next->next;
			next = next->next;
		}
	}
}

ActionManager::ActionManager() :
	activePriority(0),
	actionQueue(NULL),
	active(NULL)
{
}

void ActionManager::Execute()
{
	
	RunActive();
}
