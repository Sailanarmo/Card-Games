#pragma once

#include <cstdint>


namespace Poker
{
  class State
  {
    public:
      enum class CurrentState : uint8_t
      {
        PreFlop = 0,
        Flop,
        Turn,
        River,
        Showdown
      };

      State();

      auto SetState(const CurrentState state) -> void;
      auto GetState() const -> CurrentState;

    
    private:
      CurrentState m_currentState;
  };
}