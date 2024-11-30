//#include <iostream>
#include <utility>
#include <unordered_map>
#include "helperfunctions.h"
#include "Player.h"


int main(){
  std::unordered_map<int,int> deck;
  //std::pair<int,int> player;
  int dealer;
  std::pair<int,int> blackJackPayout;
  Player player = Player(); 
  start_game(deck,dealer, blackJackPayout, player);
 
  return 0;
}
