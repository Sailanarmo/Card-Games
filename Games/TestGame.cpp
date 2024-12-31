#include "Deck/deck.hpp"

#include <print>

auto main() -> int
{
  auto deck = std::make_unique<Deck::Deck>();
  std::println("Built Deck");
  deck->PrintDeck();
  std::println("Shuffling Deck");
  deck->Shuffle();
  deck->PrintDeck();
}