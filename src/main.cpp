//#include <iostream>
#include <utility>
#include <unordered_map>
#include "helperfunctions.h"


int main(){
  std::unordered_map<int,int> deck;
  //std::pair<int,int> player;
  int dealer;
  std::pair<int,int> blackJackPayout;
  start_game(deck,dealer, blackJackPayout);
 
  return 0;
}
