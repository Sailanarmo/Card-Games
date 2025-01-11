#include "Player/player.hpp"
#include "Table/table.hpp"
#include "Deck/card.hpp"

#include <memory>
#include <ranges>
#include <algorithm>
#include <print>

using GoFishPlayer = std::unique_ptr<GoFish::GoFishPlayer>;

auto main() -> int
{
  auto table = std::make_unique<GoFish::GoFishTable>();
  
  std::vector<GoFishPlayer> players;
  players.push_back(std::make_unique<GoFish::GoFishPlayer>("Tony"));
  players.push_back(std::make_unique<GoFish::GoFishPlayer>("Moi"));
  players.push_back(std::make_unique<GoFish::GoFishPlayer>("Ryan"));
  players.push_back(std::make_unique<GoFish::GoFishPlayer>("Peter"));

  std::ranges::for_each(players,[&table](auto& player){
    auto card = table->DealInitialCard();
    player->TakeInitialCard(std::move(card)); 
  });

  const auto lowestCardHolder = std::ranges::min_element(players,[](const auto& playerA, const auto& playerB){
    return playerA->GetInitialCardRank() < playerB->GetInitialCardRank();
  });

  std::println("The lowest card holder is: {} with Card: {}", lowestCardHolder[0]->Name(), Deck::ToString(lowestCardHolder[0]->GetInitialCardRank()));

  // Rotate the vector so that the lowest card holder is at the beginning
  std::ranges::rotate(players.begin(), lowestCardHolder, players.end());
  std::ranges::reverse(players.begin() + 1, players.end());

  std::println("Players after rotation:");
  std::ranges::for_each(players, [](const auto& player){
    std::println("Player: {}", player->Name());
  });
  return 0;
}