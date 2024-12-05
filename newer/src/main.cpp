#include "Sim.h"
#include <vector>
#include <unordered_map>
#include <string>

std::vector<int> vec_map(std::unordered_map<int,int> &dic, int c1, int c2, int d1){
  dic[c1] -=1;
  dic[c2] -=1;
  dic[d1] -=1;

  std::vector<int> vec;
  for (auto const& [key, val] : dic){
    for (int i=0; i<val; ++i){
      vec.push_back(key);
    } 
  }
  return vec;
}

int main(){
  std::unordered_map<ACTION, std::string> act_to_string = 
    {
      {HIT, "HIT"},
      {STAY, "STAY"},
      {BUST, "ERROR ERROR GOT BUST THIS SHOULD NEVER HAPPEN ERROR ERROR ERROR"} 
  };
  std::vector<int> cards;
  std::unordered_map<int,int> dic;
  for (int i=1;i<10;++i){
      dic[i] = 4;
  }
  dic[10] = 16;
  int d1,c1,c2;
  d1 = 10;
  c1 = 2;
  c2 = 3;
  cards = vec_map(dic, c1,c2,d1);
  ACTION action = run_sim(cards,c1,c2,d1);

  std::cout << "WITH THE DEALER SHOWING " << d1 << "\n";
  std::cout << "AND YOU HAVING " << c1 << ", " << c2 << "\n";
  std::cout << "THE BEST COURSE OF ACTION WAS TO " << act_to_string[action] << "\n";

}
