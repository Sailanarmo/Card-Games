#include "deck.hpp"
#include "card.hpp"

#include <ranges>
#include <algorithm>
#include <random>
#include <iostream>
#include <print>

namespace Deck
{
  Deck::Deck()
  {
    this->Build();
  }

  auto Deck::Distribute() -> std::unique_ptr<Card>
  {
    auto toDistribute = std::move(m_deck.back());
    m_deck.pop_back();
    return std::move(toDistribute);
  }

  auto Deck::Build() -> void
  {
      for(const auto face : enum_range(Suite::begin, Suite::end))
      {
        for(const auto val : enum_range(Rank::begin, Rank::end))
        {
          m_deck.push_back(std::make_unique<Card>(face,val));
        }
      }
  }

  auto Deck::Shuffle() -> void
  {
    std::random_device rd;
    std::mt19937 gen {rd()};
    std::ranges::shuffle(m_deck, gen);
  }

  auto Deck::PrintDeck() -> void
  {
    for(const auto& card : m_deck)
    {
      std::cout << "Suite: " << card->FaceName() << " Value: " << card->RankName() << std::endl;
    }
  }

  auto Deck::Rebuild(std::vector<std::unique_ptr<Card>>&& cards) -> void
  {
    std::ranges::move(cards,std::back_inserter(m_deck));
  }

  auto Deck::PrintDeckSize() -> void
  {
    std::println("Current Deck Size: {}", m_deck.size());
    std::println("");
  }
}