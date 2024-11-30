#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <unordered_map>
#include <unordered_set>
#include <string>

const std::unordered_set<std::string> VALID_VALS = {
    "1","2","3","4","5","6","7","8","9","10", 
    "11","12","13","14","t","T","j", "J", 
    "q", "Q", "k", "K", "a","A" 
  };

const std::unordered_map<std::string,int> VAL_DIC = {
    {"1",1}, {"2",2}, {"3",3}, {"4",4}, {"5",5}, {"6",6},
    {"7",7}, {"8",8}, {"9",9}, {"10",10}, {"11",10}, {"12",12},
    {"13",13}, {"14",1}, {"t",10}, {"T",10}, {"j",11},{"J",11},
    {"q",12},{"Q",12}, {"k",13}, {"K",13}, {"a",1}, {"A",1}
  };

const int NUM_CARDS = 52;

#endif
