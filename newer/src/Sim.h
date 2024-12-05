#ifndef SIM_H
#define SIM_H

#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Player.h"

enum RESULT{
  PUSH,
  WIN,
  LOSE
};

ACTION sum_results(int *hit_sums, int *stay_sums);
int getDealerSecondCard(std::vector<int>& vec, int card);
int getRandomCard(std::vector<int>& vec);
ACTION run_sim(std::vector<int> &cards, int c1, int c2, int d1);
void hit(std::vector<int> cards, int c1, int c2, int d1, RESULT &result);
void stay(std::vector<int> cards, int c1, int c2, int d1, RESULT &result);

#endif
