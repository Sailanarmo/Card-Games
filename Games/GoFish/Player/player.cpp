#include "player.hpp"

#include "Deck/card.hpp"

#include <ranges>
#include <algorithm>
#include <print>

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

  auto GoFishPlayer::TakeInitialCard(Card&& card) -> void
  {
    m_initialCardRank = card->Value();
    AddCard(std::move(card));
  }

  auto GoFishPlayer::GetInitialCardRank() const -> Deck::Rank
  {
    return m_initialCardRank;
  }

  auto GoFishPlayer::AddCard(Card&& card) -> void
  {
    auto rank = card->Value();
    m_hand[rank].push_back(std::move(card));

    if(m_hand[rank].size() == 4)
      PlaceBook();
  }

  auto GoFishPlayer::ForfeitCard(const Deck::Rank rank) -> Card
  {
    auto card = std::move(m_hand[rank].back());
    m_hand[rank].pop_back();

    // to remove the key if the vector is empty
    if(m_hand[rank].empty())
      m_hand.erase(rank);

    return card;
  }

  auto GoFishPlayer::PlaceBook() -> Book
  {
    auto book = Book();

    for(int i = 0; i < 4; i++)
    {
      book.push_back(std::move(m_hand[book.back()->Value()].back()));
      m_hand[book.back()->Value()].pop_back();
    }

    m_hand.erase(book.back()->Value());

    return book;
  }

  auto GoFishPlayer::PrintHand() -> void
  {
    std::println("Player: {}", m_name);
    std::ranges::for_each(m_hand, [this](const auto& book){
      std::ranges::for_each(book.second,[](const auto& card){
        std::print("[{}-{}] ", card->RankName(), card->FaceName());
      });
      std::println("");
    });
    std::println("");
  }
}