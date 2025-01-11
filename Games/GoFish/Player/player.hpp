#pragma once

#include "Deck/cardTypes.hpp"
#include "Player/basePlayer.hpp"

#include <memory>
#include <stack>

namespace Deck
{
  class Card;
}

namespace GoFish
{

  using Card = std::unique_ptr<Deck::Card>;
  using Book = std::stack<Card>;

  class GoFishPlayer : public Player::BasePlayer
  {
    public:
      GoFishPlayer(const std::string_view name);
      ~GoFishPlayer() = default;

      auto Name() const -> std::string_view override { return m_name; }
      auto RequestCard(const Deck::Rank rank) -> Card;

    private:
      
      // A map to a Book of Cards of that Rank. Maybe vector would be better?
      std::unordered_map<Deck::Rank, Book> m_hand;

      auto AddCard(Card&& card) -> void;
      auto ForfeitCard(const Deck::Rank rank) -> Card;
      auto PlaceBook() -> Book;

  };
}