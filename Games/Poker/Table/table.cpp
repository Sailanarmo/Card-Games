#include "table.hpp"
#include "Deck/card.hpp"

#include <print>
#include <ranges>
#include <algorithm>

namespace Poker
{
  PokerTable::PokerTable()
  {
    std::ranges::fill(m_cards, nullptr);
  }

  auto PokerTable::DisplayTable() -> void
  {
    if(m_cards[0] == nullptr)
    {
      std::println("There are no cards on the Table.");
      std::println("");
      return;
    }

    std::println("Current Table");
    std::ranges::for_each(m_cards,[](const auto& card){
      if(card != nullptr)
        std::print("[{}-{}] ", card->RankName(), card->FaceName());
    });
    std::println("");
    std::println("");
  }

  // Logic seems sounds to always have a constant lookup.
  auto PokerTable::HandleCard(Card&& card) -> void
  {
    if(m_cards[m_pos] == nullptr)
    {
      m_cards[m_pos] = std::move(card);
      m_pos += 1;
    }
  }

  auto PokerTable::ReturnCards() -> std::vector<Card>
  {
    std::vector<Card> toReturn;

    // This should set to nullptr automatically because of move semantics.
    std::ranges::transform(m_cards, std::back_inserter(toReturn),[](auto&& card){
      if(card != nullptr)
        return std::move(card);
    });

    // Reset the position to 0
    m_pos = 0;

    return toReturn;
  }
};