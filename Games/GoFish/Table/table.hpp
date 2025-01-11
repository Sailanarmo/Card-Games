#pragma once

#include "Deck/cardTypes.hpp"

#include <stack>
#include <array>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Deck
{
  class Card;
}

namespace GoFish
{
  class GoFishTable
  {
    public:
      using Card = std::unique_ptr<Deck::Card>;
      using Ocean = std::stack<Card>;
      using Book = std::array<Card,4>;
      using Books = std::unordered_map<Deck::Rank, Book>;

      GoFishTable();
      ~GoFishTable() = default;

      auto DisplayTable() -> void;
      auto DisplayBooks() -> void;
      auto HandleBook(std::stack<Card>&& book) -> void;
      auto LendOcean() -> Ocean;
      auto ReturnOcean(Ocean&& ocean) -> void;
      auto DealInitialCard() -> Card;

    private:
      Ocean m_ocean;
      Books m_books;
  };
}