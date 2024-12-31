#include "dealer.hpp"
#include "Deck/deck.hpp"
#include "Deck/card.hpp"

namespace Poker
{
  PokerDealer::PokerDealer()
  {
    m_deck = std::make_unique<Deck::Deck>();
    m_deck->Shuffle();
  }

  auto PokerDealer::ReShuffle() -> void
  {
    m_deck->Shuffle();
  }

  auto PokerDealer::PrintDeckInfo() -> void
  {
    m_deck->PrintDeckSize();
  }

  // Need to move the contents from the deck to the Player.
  // Dealer doesn't need to know the player, just needs to know
  // how many cards to dish out.
  auto PokerDealer::Deal() -> std::pair<Card,Card>
  {
    return std::make_pair(
      std::move(m_deck->Distribute()), 
      std::move(m_deck->Distribute())
    );
  }

  // To Table
  auto PokerDealer::MakePlay() -> Card
  {
    Discard();
    return std::move(this->PlayCard());
  }

  // Simply capture the cards and perform perfect forwarding.
  auto PokerDealer::HandleFold(Card&& cardA, Card&& cardB) -> void
  {
    this->Discard(std::forward<Card>(cardA),std::forward<Card>(cardB));
  }

  auto PokerDealer::Discard() -> void
  {
    m_discardPile.push_back(std::move(m_deck->Distribute()));
  }

  // Handles a players cards
  auto PokerDealer::Discard(Card&& cardA, Card&& cardB) -> void
  {
    m_discardPile.push_back(std::move(cardA));
    m_discardPile.push_back(std::move(cardB));
  }

  auto PokerDealer::PlayCard() -> Card
  {
    return std::move(m_deck->Distribute());
  }

  auto PokerDealer::CleanUp(std::vector<Card>&& tableCards) -> void
  {
    m_deck->Rebuild(std::forward<std::vector<Card>>(tableCards));
    m_deck->Rebuild(std::forward<std::vector<Card>>(m_discardPile));
  }
}
