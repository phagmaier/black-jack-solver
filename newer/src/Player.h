#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

enum ACTION{
  HIT,
  BUST,
  STAY
};

class Player{
private:
  int c1;
  int c2;
  int regSum;
  int aceSum;
  bool ace;
  int best_value;
  bool seventeen;
  bool bust;
  ACTION action;

public:
  Player(int c1, int c2);
  inline Player() : c1{0},c2{0},regSum{0},aceSum{0},ace{false},best_value{0},seventeen{false},bust{false},action{HIT}{};
  void add_card(int card);
  inline bool is_seventeen(){return seventeen;}
  inline bool busted(){return bust;}
  inline ACTION get_action(){return action;}
  inline int get_best_value(){return best_value;}
  void print_cards(bool player);
};

#endif
