#include "states.hpp"

namespace Poker
{
  State::State() : m_currentState(CurrentState::PreFlop){}

  auto State::SetState(const CurrentState state) -> void
  {
    m_currentState = state;
  }

  auto State::GetState() const -> CurrentState
  {
    return m_currentState;
  }
}