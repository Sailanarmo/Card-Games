#include "player.hpp"
#include "Deck/card.hpp"

#include <print>

namespace Poker
{
  PokerPlayer::PokerPlayer(const std::string_view name) : BasePlayer(name)
  {
    // Setting default to $1k
    m_funds = 1000;
  }

  auto PokerPlayer::UpdateHand(Card&& cardA, Card&& cardB) -> void
  {
    m_hand.first = std::move(cardA);
    m_hand.second = std::move(cardB);
  }

  auto PokerPlayer::ReturnCards() -> std::pair<Card,Card>
  {
    return std::make_pair(std::move(m_hand.first), std::move(m_hand.second));
  }

  auto PokerPlayer::Name() -> std::string_view const 
  {
    return m_name;
  }

  auto PokerPlayer::PrintPlayerInfo() -> void
  {
    std::println("Player's name: {}", this->Name());
    std::println("Player's Hand: [{}-{}], [{}-{}]", 
      m_hand.first->RankName(), m_hand.first->FaceName(), 
      m_hand.second->RankName(), m_hand.second->FaceName()
    );
    std::println("Player's Funds: ${}", m_funds);
    std::println("");
  }

}