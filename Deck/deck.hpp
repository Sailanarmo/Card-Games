#pragma once

#include <vector>
#include <memory>

namespace Deck
{
  class Card;

  class Deck
  {
    public:
      Deck();
      ~Deck() = default;

      auto Shuffle() -> void;
      auto PrintDeck() -> void;
      auto PrintDeckSize() -> void;
      auto Distribute() -> std::unique_ptr<Card>;
      auto Rebuild(std::vector<std::unique_ptr<Card>>&& cards) -> void;

    private:
      auto Build() -> void;
      std::vector<std::unique_ptr<Card>> m_deck; 

  };
}
