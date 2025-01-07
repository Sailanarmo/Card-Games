#include "Player/player.hpp"
#include "Dealer/dealer.hpp"
#include "Table/table.hpp"
#include "Logic/hands.hpp"
#include "Deck/deck.hpp"
#include "Deck/card.hpp"


#include <ranges>
#include <algorithm>
#include <print>

using PokerPlayer = std::unique_ptr<Poker::PokerPlayer>;

auto main() -> int
{
  // Dealer automatically shuffles Deck on Creation
  auto dealer = std::make_unique<Poker::PokerDealer>();
  auto table = std::make_unique<Poker::PokerTable>();
  auto parser = std::make_unique<Poker::HandParser>();

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
    auto dealtHand = dealer->Deal();
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

  auto tableHand = table->GetCards();

  auto combinedHands = std::array<const Deck::Card*,7>{};
  std::ranges::fill(combinedHands,nullptr);
  std::ranges::copy(tableHand,std::begin(combinedHands));

  auto winningHands = std::vector<std::pair<const std::string_view,Poker::HandParser::Weight>>{};
  std::ranges::transform(players, std::back_inserter(winningHands), [combinedHands,&parser](const auto& player){
    auto copyHands = combinedHands;
    auto playerHand = player->GetHand();
    copyHands[5] = playerHand.first;
    copyHands[6] = playerHand.second;
    return std::make_pair(player->Name(),parser->GetHighestRank(copyHands));
  });

  std::ranges::for_each(winningHands, [&](const auto& player){
    std::println("Player: {} - Winning Hand: {}", player.first, parser->GetWeight(player.second));
  });

  auto winner = std::ranges::max_element(winningHands, [](const auto& playerA, const auto& playerB){
    return playerA.second < playerB.second;
  });

  std::println("The winner is: {}.", std::string(winner[0].first));

  // TODO: FUTURE
  // For each player still playing call the ReturnCards function and give to dealer  
  std::ranges::for_each(players, [&dealer](auto& player){
    auto cards = std::move(player->ReturnCards());
    dealer->HandleFold(std::move(cards.first), std::move(cards.second));
  });

  dealer->CleanUp(table->ReturnCards());
  
}