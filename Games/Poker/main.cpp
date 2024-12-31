#include "Player/player.hpp"
#include "Dealer/dealer.hpp"
#include "Table/table.hpp"
#include "Deck/deck.hpp"
#include "Deck/card.hpp"

#include <ranges>
#include <algorithm>

using PokerPlayer = std::unique_ptr<Poker::PokerPlayer>;

auto main() -> int
{
  // Dealer automatically shuffles Deck on Creation
  auto dealer = std::make_unique<Poker::PokerDealer>();
  auto table = std::make_unique<Poker::PokerTable>();

  // TODO: Make dyanmic
  std::vector<PokerPlayer> players;
  players.push_back(std::make_unique<Poker::PokerPlayer>("Tony"));
  players.push_back(std::make_unique<Poker::PokerPlayer>("Moi"));
  players.push_back(std::make_unique<Poker::PokerPlayer>("Ryan"));
  players.push_back(std::make_unique<Poker::PokerPlayer>("Peter"));

  // TODO: Create another vector of Currently Playing Players. Or maybe
  //       A map since it will be easy to remove them by name or set
  //       Their status to false when they have folded for the round.
  
  //For each of the players, deal them two cards.
  std::ranges::for_each(players, [&dealer](auto& player){
    dealer->PrintDeckInfo();
    auto dealtHand = dealer->Deal();
    dealer->PrintDeckInfo();
    player->UpdateHand(std::move(dealtHand.first),std::move(dealtHand.second));
  });

  // For debugging. 
  std::ranges::for_each(players, [](const auto& player){
      player->PrintPlayerInfo();
    }
  );

  // Dealer hands card to the table. 
  table->HandleCard(std::move(dealer->MakePlay()));
  table->HandleCard(std::move(dealer->MakePlay()));
  table->HandleCard(std::move(dealer->MakePlay()));
  table->DisplayTable();

  table->HandleCard(std::move(dealer->MakePlay()));
  table->DisplayTable();

  table->HandleCard(std::move(dealer->MakePlay()));
  table->DisplayTable();

  // TODO: FUTURE
  // For each player still playing call the ReturnCards function and give to dealer  
  std::ranges::for_each(players, [&dealer](auto& player){
    auto cards = std::move(player->ReturnCards());
    dealer->HandleFold(std::move(cards.first), std::move(cards.second));
  });

  dealer->CleanUp(table->ReturnCards());
  
}