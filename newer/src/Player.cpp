#include "Player.h"

Player::Player(int c1,int c2) : c1{c1},c2{c2}{
  regSum = c1+c2;
  aceSum = regSum;
  ace = c1 == 1 || c2 == 1;
  aceSum += ace ? 10 : 0;
  best_value = ace ?  aceSum  : regSum;
  seventeen = best_value >= 17 ? true : false;
  bust = false;
  action = seventeen ? STAY : HIT;
}

void Player::add_card(int card){
  regSum +=card;
  if (ace){
    aceSum +=card;
  }
  else if(card == 1){
    aceSum += 11;
    ace=true;
  }
  else{
    aceSum +=card;
  }
  if (regSum > 21){
    bust = true;
    seventeen = false;
    action = BUST;
    return;
  }
  if(aceSum >= 17 && aceSum < 22){
    seventeen = true;
    best_value = aceSum;
    action = STAY;
    return;
  }
  if (regSum >= 17 && aceSum < 22){
    seventeen = true;
    best_value = regSum;
    action = STAY;
    return;
  }
  seventeen = false;
  best_value = aceSum < 22 ? aceSum : regSum;
  action = HIT;
}

void Player::print_cards(bool player){
  if (player){
    std::cout << "PLAYERS CARDS ARE: " << c1 << ", " << c2 << "\n";
  }
  else{
    std::cout << "DEALERS CARDS ARE: " << c1 << ", " << c2 << "\n";
  }
}
