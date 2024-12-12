#include "Parser.h"

Parser::Parser(const std::string &fileName){
  std::unordered_map<int,int> dead_player_cards;
  std::ifstream file(fileName);
  if (!file.is_open()){
    std::cerr << "ERROR COULD NOT OPEN FILE\n"; 
    return;
  }
  std::string tmp; 
  getline(file,tmp);
  decks = std::stoi(tmp);

  for (int i=1;i<10;++i){
    deck[i]=4 * decks;
  }
  deck[10] = 16 * decks;

  getline(file,tmp);
  player_cards.first = std::stoi(tmp);
  deck[player_cards.first] -=1;
  getline(file,tmp);
  player_cards.second = std::stoi(tmp);
  deck[player_cards.second] -=1;
  getline(file,tmp);
  dealer_card = std::stoi(tmp);
  deck[dealer_card] -=1;

  
  int card;
  std::string str;
  for (int i=0;i<10;++i){
    getline(file,tmp);
    for (char c: tmp){
      if (c == ' '){
        card = std::stoi(str);
        str = "";
      }
      else{
        str += c; 
      }
    }
    dead_player_cards[card] = std::stoi(str);
  }
  for (int i=0;i<10;++i){
    getline(file,tmp);
    for (char c: tmp){
      if (c == ' '){
        card = std::stoi(str);
        str = "";
      }
      else{
        str += c; 
      }
    }
    deck[card] -= std::stoi(str);
  } 

  file.close();

  for (auto &[card,value] : dead_player_cards){
    for (int i=0;i<value;++value){
      p1_dead_cards.push_back(card);
    }
  }
}
