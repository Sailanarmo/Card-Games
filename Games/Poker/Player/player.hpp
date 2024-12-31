#pragma once

#include "Player/basePlayer.hpp"

#include <cstdint>
#include <utility>
#include <memory>

namespace Deck
{
  class Card;
}

namespace Poker
{
  
  using Card = std::unique_ptr<Deck::Card>;

  class PokerPlayer : public Player::BasePlayer
  {
    public:
      PokerPlayer(const std::string_view name);
      ~PokerPlayer() = default;

      auto UpdateHand(Card&& cardA, Card&& cardB) -> void;
      auto ReturnCards() -> std::pair<Card,Card>;
      auto Name() -> std::string_view const override;


      // For debugging
      auto PrintPlayerInfo() -> void;
    
    private:
      uint_fast32_t m_funds{0};
      std::pair<Card,Card> m_hand;

  };
}