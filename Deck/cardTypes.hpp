#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <concepts>
#include <ranges>
#include <utility>

namespace Deck
{
    enum class Suite : int
    {
      Spade = 0,
      Heart,
      Club,
      Diamond,
      begin = 0,
      end = Diamond
    };

    enum class Rank : int
    {
      Two = 0,
      Three,
      Four,
      Five,
      Six,
      Seven,
      Eight,
      Nine,
      Ten,
      Jack,
      Queen,
      King,
      Ace,
      begin = 0,
      end = Ace
    };

    static const std::unordered_map<Suite, std::string> suiteMap = {
        {Suite::Spade, std::string{"Spade"}},
        {Suite::Heart, std::string{"Heart"}},
        {Suite::Club, std::string{"Club"}},
        {Suite::Diamond, std::string{"Diamond"}},
    };

    static const std::unordered_map<Rank, std::string> rankMap = {
        {Rank::Two, "2"},
        {Rank::Three, "3"},
        {Rank::Four, "4"},
        {Rank::Five, "5"},
        {Rank::Six, "6"},
        {Rank::Seven, "7"},
        {Rank::Eight, "8"},
        {Rank::Nine, "9"},
        {Rank::Ten, "10"},
        {Rank::Jack, "Jack"},
        {Rank::Queen, "Queen"},
        {Rank::King, "King"},
        {Rank::Ace, "Ace"},
    };

    template<typename T>
    auto ToString(const T value) -> std::string_view const
    {
      if constexpr (std::same_as<T, Suite>)
        return suiteMap.at(value);
      else if constexpr (std::same_as<T, Rank>)
        return rankMap.at(value);
    }

    constexpr inline auto enum_range(auto first, auto last)
    {
        auto enum_range = 
          std::views::iota(
            std::to_underlying(first),
            std::to_underlying(last) + 1
          )
          | std::views::transform(
              [](auto enum_val) { return (decltype(first))enum_val; }
          );
        
        return enum_range;
    }
}