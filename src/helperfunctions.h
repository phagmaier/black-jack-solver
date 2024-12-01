#ifndef HELPERFUCTIONS_H
#define HELPERFUCTIONS_H
#include "constants.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <random>

enum TRIPLE {
    BUST,
    HIT,
    STAY 
};

float get_blackJack_payout(float bet, std::pair<int,int> &fraction);

inline bool is_int(std::string& str)
{
    return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}

std::vector<int> make_deck_vector(std::unordered_map<int,int> &dic);

int get_num_decks();

int get_card_val();

void get_dealers_hand(int& dealer);

void get_players_hand(std::pair<int, int>& player);

void make_deck(std::unordered_map<int, int>& deck, int num_decks, std::pair<int, int>& hand, int dealer);

void set_21_payout(std::pair<int, int>& fraction);

void get_dead_cards(std::unordered_map<int, int>& deck);

int get_deck_size(std::unordered_map<int, int>& deck);

int decision(TRIPLE action, std::vector<int> &deck, int reg_sum, int ace_sum, bool ace, std::vector<int> &discarded);

//bool because we are assuming dealer doesn't have 21 
//if you are looking at optimal strat to take
int get_random_card(std::vector<int>& vec, bool second_card);


std::unordered_map<int, float> get_percentages(std::unordered_map<int, int>& prct);

int get_best_val(int regular, int ace);

TRIPLE get_dealer_action(int regular, int ace);

void get_sum(int &reg_sum, int &ace_sum, int card, bool &ace);

int hit(std::vector<int> &deck, int reg_sum, int ace_sum, bool ace, std::vector<int> &discarded);

std::unordered_map<int,int> simulation(std::unordered_map<int,int> &dic_deck, int dealer_card1, std::pair<int,int> &player);

void start_game(std::unordered_map<int, int>& deck, int& dealer, std::pair<int, int>& payout);

#endif
