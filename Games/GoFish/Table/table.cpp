#include "table.hpp"
#include "Deck/deck.hpp"
#include "Deck/card.hpp"

#include <print>
#include <ranges>
#include <algorithm>

namespace GoFish
{
    // Create a deck, shuffle it, and then move it to the ocean.
    GoFishTable::GoFishTable()
    {
      auto deck = std::make_unique<Deck::Deck>();
      deck->Shuffle();
      std::ranges::for_each(deck->MoveDeck(),[this](auto&& card){
        m_ocean.push(std::move(card));
      });
      std::println("Ocean Size: {}", m_ocean.size());
    }

    auto GoFishTable::DealInitialCard() -> Card
    {
      auto card = std::move(m_ocean.top());
      m_ocean.pop();
      return card;
    }
    
    auto GoFishTable::DisplayTable() -> void
    {
    }
    
    auto GoFishTable::DisplayBooks() -> void
    {
    }
    
    auto GoFishTable::HandleBook(std::stack<Card>&& book) -> void
    {
      auto rank = book.top()->Value();
      m_books[rank] = Book();
    
      // Size should be 4
      for(int i = 0; i < book.size(); i++)
      {
        m_books[rank][i] = std::move(book.top());
        book.pop();
      }

    }
    
    auto GoFishTable::LendOcean() -> Ocean
    {
        return std::move(m_ocean);
    }
    
    auto GoFishTable::ReturnOcean(Ocean&& ocean) -> void
    {
        m_ocean = std::move(ocean);
    }
}