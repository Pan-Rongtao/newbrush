#include "newbrush/StateManager.h"

using namespace nb;

void State::assignProperty(ref<Object> obj, property pro, const var & value)
{
	m_pros.push_back(ObjectTriplet{ obj, pro, value });
}

StateManager::StateManager()
	: m_currentStateIndex(-1)
{
}

StateManager::StateManager(uint32_t stateCount)
	: m_currentStateIndex(-1)
{
	m_states.reserve(stateCount);
	for (auto i = 0u; i < stateCount; ++i)
		m_states.push_back(createRef<State>());
}

void StateManager::addState(ref<State> state)
{
	m_states.push_back(state);
}

uint32_t StateManager::stateCount() const
{
	return m_states.size();
}

ref<State> &StateManager::operator[](uint32_t index)
{
	nbThrowExceptionIf(index >= stateCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)stateCount());
	return m_states[index];
}

int StateManager::currentStateIndex() const
{
	return m_currentStateIndex;
}

void StateManager::gotoState(uint32_t index)
{
	nbThrowExceptionIf(index >= stateCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)stateCount());
	gotoState(m_states[index]);
}

void StateManager::gotoState(ref<State> state)
{
	nbThrowExceptionIf(!state, std::invalid_argument, "state is nullptr");
	if (m_currentStateIndex != -1 && state == m_states[m_currentStateIndex]) return;

	for (auto i = 0u; i < m_states.size(); ++i)
	{
		auto const &s = m_states[i];
		if (state == s)
		{
			for (auto const &objTriplet : s->m_pros)
			{
				objTriplet.object->setValue(objTriplet.prop, objTriplet.value);
			}
			m_currentStateIndex = i;
		}
	}
}

void StateManager::gotoPrevState()
{
	if (m_states.empty())
		return;

	auto state = m_currentStateIndex - 1;
	if (state == -1)
		state = m_states.size() - 1;
	gotoState(state);
}

void StateManager::gotoNextState()
{
	if (m_states.empty())
		return;

	auto state = m_currentStateIndex + 1;
	if (state == m_states.size())
		state = 0;
	gotoState(state);
}