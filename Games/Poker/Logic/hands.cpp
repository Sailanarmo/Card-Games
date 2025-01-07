#include "hands.hpp"
#include "Deck/card.hpp"

#include <ranges>
#include <algorithm>
#include <print>

namespace Poker
{
  constexpr uint_fast8_t fullHouseValue = 5;

  const HandParser::Flushes HandParser::m_flushes = {
    {std::array<Deck::Suite,5>{
      Deck::Suite::Spade, Deck::Suite::Spade, Deck::Suite::Spade, Deck::Suite::Spade, Deck::Suite::Spade}, 
      Weight::Flush},
    {std::array<Deck::Suite,5>{
      Deck::Suite::Heart, Deck::Suite::Heart, Deck::Suite::Heart, Deck::Suite::Heart, Deck::Suite::Heart}, 
      Weight::Flush},
    {std::array<Deck::Suite,5>{
      Deck::Suite::Club, Deck::Suite::Club, Deck::Suite::Club, Deck::Suite::Club, Deck::Suite::Club}, 
      Weight::Flush},
    {std::array<Deck::Suite,5>{
      Deck::Suite::Diamond, Deck::Suite::Diamond, Deck::Suite::Diamond, Deck::Suite::Diamond, Deck::Suite::Diamond}, 
      Weight::Flush},
  };

  const HandParser::Straights HandParser::m_straights = {
    {std::array<Deck::Rank,5>{
      Deck::Rank::Five, Deck::Rank::Four, Deck::Rank::Three, Deck::Rank::Two, Deck::Rank::Ace
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Six, Deck::Rank::Five, Deck::Rank::Four, Deck::Rank::Three, Deck::Rank::Two
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Seven, Deck::Rank::Six, Deck::Rank::Five, Deck::Rank::Four, Deck::Rank::Three
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Eight, Deck::Rank::Seven, Deck::Rank::Six, Deck::Rank::Five, Deck::Rank::Four
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Nine, Deck::Rank::Eight, Deck::Rank::Seven, Deck::Rank::Six, Deck::Rank::Five
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Ten, Deck::Rank::Nine, Deck::Rank::Eight, Deck::Rank::Seven, Deck::Rank::Six
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Jack, Deck::Rank::Ten, Deck::Rank::Nine, Deck::Rank::Eight, Deck::Rank::Seven
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Queen, Deck::Rank::Jack, Deck::Rank::Ten, Deck::Rank::Nine, Deck::Rank::Eight
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::King, Deck::Rank::Queen, Deck::Rank::Jack, Deck::Rank::Ten, Deck::Rank::Nine
    }, Weight::Straight},
    {std::array<Deck::Rank,5>{
      Deck::Rank::Ace, Deck::Rank::King, Deck::Rank::Queen, Deck::Rank::Jack, Deck::Rank::Ten
    }, Weight::Straight}
  };

  const std::unordered_map<HandParser::Weight, std::string> HandParser::m_weightMap = {
    { HandParser::Weight::High, "High Card"},
    { HandParser::Weight::Pair, "Pair"},
    { HandParser::Weight::TwoPair, "Two Pair"},
    { HandParser::Weight::ThreeOfAKind, "Three of a Kind"},
    { HandParser::Weight::Straight, "Straight"},
    { HandParser::Weight::Flush, "Flush"},
    { HandParser::Weight::FullHouse, "Full House"},
    { HandParser::Weight::FourOfAKind, "Four of a Kind"},
    { HandParser::Weight::StraightFlush, "Straight Flush"},
    { HandParser::Weight::RoyalFlush, "Royal Flush"}
  };

  HandParser::HandParser(){}

  auto HandParser::GetWeight(const Weight weight) const -> std::string_view
  {
    return m_weightMap.at(weight);
  }

  auto HandParser::GetHighestRank(std::array<const Deck::Card*, 7>& hand) -> Weight
  {
    auto bestRanks = std::vector<Weight>{};

    // Can check easily from here without sorting.
    //auto isFlush = FindFlush(hand);

    //if(isFlush)
      //bestRanks.push_back(Rank::Flush);

    auto findPairs = FindDuplicates(hand);
    
    // We need to check if we found anything greater than a High Card, Pair, or Three of a Kind. 
    // It should not be possible to obtain anthing else. 
    if(findPairs == Weight::High || findPairs == Weight::Pair || findPairs == Weight::ThreeOfAKind /*&& !isFlush*/)
      bestRanks.push_back(findPairs);
    else
      return findPairs;

    // Now we need to sort for the rest.
    std::ranges::sort(hand, [](const auto* cardA, const auto* cardB) { return cardA->Value() > cardB->Value(); });

    bestRanks.push_back(FindStraight(hand));

    std::ranges::sort(bestRanks, [](const auto rankA, const auto rankB){ return rankA > rankB; });

    return bestRanks[0];

  }

  auto HandParser::FindDuplicates(const std::array<const Deck::Card *, 7> &hand) -> Weight
  {
    // Count all the duplicates, if any, exist. Does not need to be sorted.  
    auto rankOccurances = std::unordered_map<Deck::Rank,uint_fast8_t>{};
    std::ranges::for_each(std::as_const(hand), [&rankOccurances](const auto* card){ rankOccurances[card->Value()]++; });

    auto uniqueKeys = uint_fast8_t{0};
    auto duplicates = uint_fast8_t{0};


    for(const auto&[rank, occurance] : rankOccurances)
    {
      if(occurance > 1)
      {
        uniqueKeys += 1;
        duplicates += occurance;
      }
    }

    if(uniqueKeys == 1 && duplicates == 2)
      return Weight::Pair;
    else if(uniqueKeys == 1 && duplicates == 3)
      return Weight::ThreeOfAKind;
    else if(uniqueKeys == 1 && duplicates == 4)
      return Weight::FourOfAKind;
    else if(uniqueKeys == 2 && duplicates == 4)
      return Weight::TwoPair;
    else if(uniqueKeys == 2 && duplicates == 5)
      return Weight::FullHouse;
    else if(uniqueKeys == 3 && duplicates == 6) // This is a unique case where something like AQQ5522 pops up. Best is still two pair
      return Weight::TwoPair;
    else
      return Weight::High;

  }

  // Array must be sorted!
  auto HandParser::FindStraight(const std::array<const Deck::Card *, 7> &hand) -> Weight
  {
    auto winningHands = std::vector<std::pair<std::array<Deck::Suite,5>, std::array<Deck::Rank, 5>>>{};
    auto endPos = std::size_t{3};

    for(auto pos = 0; pos < endPos; ++pos)
    {
      auto winningHand = std::array<const Deck::Card*, 5>{};
      auto suites = std::array<Deck::Suite,5>{};
      auto ranks = std::array<Deck::Rank,5>{};

      std::ranges::rotate_copy(hand, hand.begin() + pos, winningHand.begin());
      std::ranges::transform(winningHand, std::begin(suites), [](const auto* card){ return card->Face(); });
      std::ranges::transform(winningHand, std::begin(ranks), [](const auto* card){ return card->Value(); });

      // If any Aces are found at the beginning we must assume that a pair or 
      // straight can be found where the Ace is at the end. 
      if(winningHand[0]->Value() == Deck::Rank::Ace)
        endPos += 1;

      winningHands.push_back(std::make_pair(suites,ranks));
    } 

    for(const auto& hand : winningHands)
    {
      auto isStraight = false;
      auto isFlush = false;

      if(m_straights.contains(hand.second))
        isStraight = true;
      
      if(m_flushes.contains(hand.first))
        isFlush = true;
      
      if(isStraight && isFlush && hand.second[0] == Deck::Rank::Ace)
        return Weight::RoyalFlush;

      if(isStraight && isFlush)
        return Weight::StraightFlush;
      
      if(isStraight)
        return Weight::Straight;
      
      if(isFlush)
        return Weight::Flush;
      
      return Weight::High;
    }
  }

  auto HandParser::FindFlush(const std::array<const Deck::Card *, 7> &hand) -> bool
  {
    auto faceOccurances = std::unordered_map<Deck::Suite,uint_fast8_t>{};
    std::ranges::for_each(std::as_const(hand), [&faceOccurances](const auto* card){ faceOccurances[card->Face()]++; });

    for(const auto&[face, occurance] : faceOccurances)
    {
      if(occurance >= 5)
        return true;
    }

   return false;

  }
}