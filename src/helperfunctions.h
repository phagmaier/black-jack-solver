#ifndef HELPERFUCTIONS_H
#define HELPERFUCTIONS_H
#include <algorithm>
#include <string>
#include <iostream>
#include <limits>
#include <sstream>
#include "constants.h"
#include "Player.h"


inline bool is_int(std::string &str){
  return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c){return !std::isdigit(c);}) == str.end();
}

int get_num_decks();

int get_card_val();

void get_dealers_hand(int &dealer);

void get_players_hand(std::pair<int,int> &player);

void make_deck(std::unordered_map<int, int> &deck, int num_decks, std::pair<int,int> &hand, int dealer);

void set_21_payout(std::pair<int,int> &fraction);


void get_dead_cards(std::unordered_map<int,int> &deck);

void start_game(std::unordered_map<int,int> &deck, int &dealer, std::pair<int,int> &payout, Player &p1);

#endif