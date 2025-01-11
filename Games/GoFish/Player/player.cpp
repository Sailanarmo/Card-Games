#include "player.hpp"

#include "Deck/card.hpp"

#include <ranges>
#include <algorithm>

namespace GoFish
{
  GoFishPlayer::GoFishPlayer(const std::string_view name) : Player::BasePlayer(name)
  {
  }

  auto GoFishPlayer::RequestCard(const Deck::Rank rank) -> Card
  {
    if(m_hand.contains(rank))
      return std::move(ForfeitCard(rank));
    else
      return nullptr;
  }

  auto GoFishPlayer::AddCard(Card&& card) -> void
  {
    m_hand[card->Value()].push(std::move(card));

    if(m_hand[card->Value()].size() == 4)
      PlaceBook();
  }

  auto GoFishPlayer::ForfeitCard(const Deck::Rank rank) -> Card
  {
    auto card = std::move(m_hand[rank].top());
    m_hand[rank].pop();

    // to remove the key if the stack is empty
    if(m_hand[rank].empty())
      m_hand.erase(rank);

    return card;
  }
}