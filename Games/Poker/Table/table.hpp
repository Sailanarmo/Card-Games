#pragma once

#include <memory>
#include <vector>
#include <array>

namespace Deck
{
  class Card;
}

namespace Poker
{
  using Card = std::unique_ptr<Deck::Card>;

  class PokerTable
  {
    public:
      PokerTable();

      auto DisplayTable() -> void;
      auto HandleCard(Card&& card) -> void;
      auto ReturnCards() -> std::vector<Card>;

    private:
      std::array<Card,5> m_cards;
      std::size_t m_pos{0}; 

  };
}
