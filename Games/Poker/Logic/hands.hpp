#pragma once

#include "Deck/cardTypes.hpp"

#include <array>
#include <vector>
#include <compare>
#include <cstdint>
#include <unordered_map>

namespace Deck
{
  class Card;
}

namespace Poker
{

  class HandParser
  {
    public:
      HandParser();

      enum class Weight : uint8_t
      {
        High = 0,
        Pair,
        TwoPair,
        ThreeOfAKind,
        Straight,
        Flush,
        FullHouse,
        FourOfAKind,
        StraightFlush,
        RoyalFlush
      };

      // Generates all logical operations for us
      friend std::strong_ordering operator<=>(Weight lhs, Weight rhs)
      {
          return static_cast<uint8_t>(lhs) <=> static_cast<uint8_t>(rhs);
      }

      auto GetHighestRank(std::array<const Deck::Card*,7>& hand) -> Weight;

      auto GetWeight(const Weight weight) const -> std::string_view;

    private:
      // Hash function for std::array
      struct ArrayHash {
          template <typename T, std::size_t N>
          std::size_t operator()(const std::array<T, N>& arr) const {
              std::size_t seed = 0;
              for (auto& elem : arr) {
                  seed ^= std::hash<T>{}(elem) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
              }
              return seed;
          }
      };

      // Equality operator for std::array
      template <typename T, std::size_t N>
      friend bool operator==(const std::array<T, N>& lhs, const std::array<T, N>& rhs) {
          return std::equal(lhs.begin(), lhs.end(), rhs.begin());
      }

      using Flushes  = std::unordered_map<std::array<Deck::Suite,5>, Weight, ArrayHash>;
      using Straights = std::unordered_map<std::array<Deck::Rank,5>, Weight, ArrayHash>;

      auto FindDuplicates(const std::array<const Deck::Card*,7>& hand) -> Weight;
      auto FindStraight(const std::array<const Deck::Card*,7>& hand) -> Weight;
      auto FindFlush(const std::array<const Deck::Card*,7>& hand) -> bool;
      static const Flushes m_flushes;
      static const Straights m_straights;
      static const std::unordered_map<Weight, std::string> m_weightMap;

      

  };

}