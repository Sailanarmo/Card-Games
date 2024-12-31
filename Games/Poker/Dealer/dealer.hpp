#pragma once

#include <memory>
#include <utility>
#include <vector>

namespace Deck
{
  class Deck;
  class Card;
}

namespace Poker
{

  using Card = std::unique_ptr<Deck::Card>;

  class PokerDealer
  {
    public:
      PokerDealer();
      ~PokerDealer() = default;


      auto Deal() -> std::pair<Card,Card>;
      auto ReShuffle() -> void;
      auto MakePlay() -> Card;
      auto HandleFold(Card&& cardA, Card&& cardB) -> void;
      auto CleanUp(std::vector<Card>&& tableCards) -> void;

      // Debug Information
      auto PrintDeckInfo() -> void;
    
    private:
      std::unique_ptr<Deck::Deck> m_deck;
      std::vector<Card> m_discardPile;

      auto Discard() -> void;
      auto Discard(Card&& cardA, Card&& cardB) -> void;
      auto PlayCard() -> Card;
  };
}