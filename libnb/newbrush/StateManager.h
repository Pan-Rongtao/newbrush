#pragma once
#include <vector>
#include "newbrush/Object.h"

namespace nb
{

class NB_API State
{
public:
	void assignProperty(ref<Object> obj, property pro, const var &value);

private:
	std::vector<ObjectTriplet> m_pros;
	friend class StateManager;
};

class NB_API StateManager
{
public:
	StateManager();
	StateManager(uint32_t stateCount);

	void addState(ref<State> state);
	uint32_t stateCount() const;
	ref<State> &operator[](uint32_t index);

	int currentStateIndex() const;

	void gotoState(uint32_t index);
	void gotoState(ref<State> state);
	void gotoPrevState();
	void gotoNextState();

private:
	std::vector<ref<State>> m_states;
	int m_currentStateIndex;
};

}