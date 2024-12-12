#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

class Parser{
private:
  //std::ifstream file;
public:
  Parser(const std::string &fileName);
  int decks = 0;
  std::pair<int,int> player_cards = {0,0};
  //std::unordered_map<int,int> dead_player_cards;
  //std::vector<int> other_dead_cards;
  std::unordered_map<int,int> deck;
  int dealer_card = 0;
  std::vector<int> p1_dead_cards;

};

#endif
