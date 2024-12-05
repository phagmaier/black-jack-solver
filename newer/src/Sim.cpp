#include "Sim.h"

ACTION sum_results(int *hit_sums, int *stay_sums){
  int hitting = hit_sums[WIN] - hit_sums[LOSE];
  int staying = stay_sums[WIN] - stay_sums[LOSE];
  if (hitting >= staying){
    return HIT;
  }
  else{
    return STAY;
  }
}




// Thread-local RNG (one per thread)
thread_local std::mt19937 gen(std::random_device{}());  // Seed once per thread

int getRandomCard(std::vector<int>& vec) {
  if (vec.empty()) {
    throw std::invalid_argument("Vector is empty.");
  }
  std::uniform_int_distribution<> dis(0, vec.size() - 1);
  int index = dis(gen);
  int number = vec[index];

  vec[index] = vec.back();
  vec.pop_back();
  return number;
}

int getDealerSecondCard(std::vector<int>& vec, int card) {
  int index;
  int number;
  if (vec.empty()) {
    throw std::invalid_argument("Vector is empty.");
  }
  std::uniform_int_distribution<> dis(0, vec.size() - 1);
  bool keepGoing = true;
  while (keepGoing){
    keepGoing = false;
    index = dis(gen);
    number = vec[index];
    if ((card == 1 && number == 10) || (card == 10 && number == 1)){
      keepGoing = true; 
    }
  }
  vec[index] = vec.back();
  vec.pop_back();
  return number;
}



void hit(std::vector<int> cards, int c1, int c2, int d1, RESULT &result){
  Player p1 = Player(c1,c2);
  Player dealer = Player(d1,getDealerSecondCard(cards,d1));
  p1.add_card(getRandomCard(cards));
  if (p1.busted()){
    result = LOSE;
    return;
  }
  ACTION action = dealer.get_action();
  int count = 0;
  while (action == HIT){
    int card = getRandomCard(cards);
    dealer.add_card(card); 
    action = dealer.get_action();
  }
  if (action == BUST){

    result = WIN;
    return;
  }
  int pVal = p1.get_best_value();
  int dVal = dealer.get_best_value();
  if (pVal > dVal){
    result = WIN;
    return;
  }
  if (dVal > pVal){
    result = LOSE;
    return;
  }
  result = PUSH;
}


void stay(std::vector<int> cards, int c1, int c2, int d1, RESULT &result){
  Player p1 = Player(c1,c2);
  Player dealer = Player(d1,getDealerSecondCard(cards,d1));
  ACTION action = dealer.get_action();
  int count = 0;
  while (action == HIT){
    int card = getRandomCard(cards);
    dealer.add_card(card); 
    action = dealer.get_action();
  }
  if (action == BUST){
    result = WIN;
    return;
  }
  int pVal = p1.get_best_value();
  int dVal = dealer.get_best_value();
  if (pVal > dVal){
    result = WIN;
    return;
  }
  if (dVal > pVal){
    result = LOSE;
    return;
  }
  result = PUSH;
}


ACTION run_sim(std::vector<int> &cards, int c1, int c2, int d1){
  int hits[3] = {0,0,0};
  int stays[3] = {0,0,0};
  const int ITERATIONS = 1000000;
  unsigned int maxThreads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  std::vector<RESULT> results; 
  results.resize(maxThreads);

  //HITS
  for (int i=0;i<ITERATIONS/maxThreads; ++i){
    for (int x=0;x<maxThreads;++x){
      threads.emplace_back(std::thread(hit,cards, c1,c2,d1,std::ref(results[x]))); 
    }
    for (int z=0;z<maxThreads;++z){
      threads[z].join();
      ++hits[results[z]];
    }
    threads.clear();
  }

  //STAYS
  for (int i=0;i<ITERATIONS/maxThreads; ++i){
    for (int x=0;x<maxThreads;++x){
      threads.emplace_back(std::thread(hit,cards, c1,c2,d1,std::ref(results[x]))); 
    }
    for (int z=0;z<maxThreads;++z){
      threads[z].join();
      ++stays[results[z]];
    }
    threads.clear();
  }   
  return sum_results(hits,stays);
}


/*
int getRandomCard(std::vector<int>& vec) {
  static std::mutex mtx;
  std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

  if (vec.empty()) {
      throw std::invalid_argument("Vector is empty.");
  }

  // Set up a random number generator
  std::random_device rd;  // Random device for seeding
  std::mt19937 gen(rd()); // Mersenne Twister RNG
  std::uniform_int_distribution<> dis(0, vec.size() - 1);
  
  int index = dis(gen);
  int number = vec[index];

  vec[index] = vec.back();
  vec.pop_back();
  return number;
}

int getDealerSecondCard(std::vector<int>& vec, int card) {
  int number;
  int index;
  static std::mutex mtx;
  std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

  if (vec.empty()) {
      throw std::invalid_argument("Vector is empty.");
  }

  // Set up a random number generator
  std::random_device rd;  // Random device for seeding
  std::mt19937 gen(rd()); // Mersenne Twister RNG
  std::uniform_int_distribution<> dis(0, vec.size() - 1);
  bool keepGoing = true;  
  while (keepGoing){
    keepGoing = false;
    index = dis(gen);
    number = vec[index];
    if ((card == 1 && number == 10) || (card == 10 && number == 1)){
      keepGoing = true;
    }
  }
  vec[index] = vec.back();
  vec.pop_back();
  return number;
}

*/
