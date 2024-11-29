#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <unordered_set>
#include <string>
#include <sstream>
#include <unordered_map>

static const int NUM_CARDS = 52;

const static std::unordered_set<std::string> valid_vals = {
    "1","2","3","4","5","6","7","8","9","10", 
    "11","12","13","14","t","T","j", "J", 
    "q", "Q", "k", "K", "a","A" 
  };

const static std::unordered_map<std::string,int> val_dic = {
    {"1",1}, {"2",2}, {"3",3}, {"4",4}, {"5",5}, {"6",6},
    {"7",7}, {"8",8}, {"9",9}, {"10",10}, {"11",10}, {"12",12},
    {"13",13}, {"14",1}, {"t",10}, {"T",10}, {"j",11},{"J",11},
    {"q",12},{"Q",12}, {"k",13}, {"K",13}, {"a",1}, {"A",1}
  };


bool is_int(std::string &str){
  return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c){return !std::isdigit(c);}) == str.end();
}

//Get the number of decks used
int get_num_decks(){
  std::string deck_string = "";
  int num_decks;
  std::cout << "Enter the number of decks used: ";
  std::cin >> deck_string;
  std::cout << "\n";

  while (!is_int(deck_string)){
    deck_string = "";
    std::cout << "I'm Sorry that was not a valid entry\n";
    std::cout << "Please enter the number of decks used: ";
    std::cin >> deck_string;
    std::cout << "\n";
  }
  num_decks = std::stoi(deck_string);
  return num_decks;
}

void get_dealers_hand(int &dealer){
  std::string c1 = "";
  std::cout << "Enter the Dealer's visible Card: ";
  std::cin >> c1;
  std::cout << "\n";
  while (valid_vals.find(c1) == valid_vals.end()){
    c1 = "";
    std::cout << "I'm Sorry that was not a valid entry\n";
    std::cout << "Please enter the card value: ";
    std::cin >> c1;
    std::cout << "\n";
  }
  auto it = val_dic.find(c1);
  if (it !=val_dic.end()){
    dealer= it->second;
  }
  else{
    std::cerr << "ERROR SHOULDN'T PRINT BAD KEY ENTERED\n";
    return;
  }
}

//if you ever expand into future 
//and take into account other peoples hands not just
//your own heads up need to ensure you aren't overflowing 
//cards i.e. someone accidently types that 6 5's were dealt
//with only one deck
//for now it's impossible but heads up
void get_players_hand(std::pair<int,int> &player){
  std::string c1 = "";
  std::cout << "Enter the First Card: ";
  std::cin >> c1;
  std::cout << "\n";
  while (valid_vals.find(c1) == valid_vals.end()){
    c1 = "";
    std::cout << "I'm Sorry that was not a valid entry\n";
    std::cout << "Please enter the card value: ";
    std::cin >> c1;
    std::cout << "\n";
  }
  auto it = val_dic.find(c1);
  if (it !=val_dic.end()){
    player.first = it->second;
  }
  else{
    std::cerr << "ERROR SHOULDN'T PRINT BAD KEY ENTERED\n";
    return;
  }

  std::string c2 = "";
  std::cout << "Enter the Second Card: ";
  std::cin >> c2;
  std::cout << "\n";
  while (valid_vals.find(c2) == valid_vals.end()){
    c2 = "";
    std::cout << "I'm Sorry that was not a valid entry\n";
    std::cout << "Please enter the card value: ";
    std::cin >> c2;
    std::cout << "\n";
  }
  auto it2 = val_dic.find(c2);
  if (it2 !=val_dic.end()){
    player.second= it2->second;
  }
  else{
    std::cerr << "ERROR SHOULDN'T PRINT BAD KEY ENTERED\n";
    return;
  }
}

//make the deck based on the number of cards
void make_deck(std::vector<int> &deck, int num_decks, std::pair<int,int> &hand, int dealer){
  for (int i=0;i<num_decks; ++i){
    for (int x=0;x<4;++x){
      for (int z=1;z<14;++z){
        deck.push_back(z);
      }
    }
  }

  //now remove the dealt cards
  auto it1 = std::find(deck.begin(), deck.end(), dealer);
  if (it1 != deck.end()){
    deck.erase(it1);
  }
  auto it2 = std::find(deck.begin(), deck.end(), hand.first);
  if (it2 != deck.end()){
    deck.erase(it2);
  }
  auto it3 = std::find(deck.begin(), deck.end(), hand.second);
  if (it3 != deck.end()){
    deck.erase(it3);
  }
}

void start_game(std::vector<int> &deck, std::pair<int,int> &player, int &dealer){
  int num_decks = get_num_decks();
  get_players_hand(player);
  get_dealers_hand(dealer);
  make_deck(deck, num_decks, player, dealer);
}

int main(){
  std::vector<int> deck;
  std::pair<int,int> player;
  int dealer;
  //std::unordered_set<int> dealt;
  start_game(deck,player,dealer);

  //testing
  std::cout << "PLAYER ONE'S HAND IS: " << player.first << ", " << player.second << "\n"; 
  std::cout << "The Dealer's HAND IS: " << dealer << "\n";

  std::unordered_map<int,int> counts;
  for (int i : deck){
    counts[i] +=1;
  }

  for (auto &i : counts){
    std::cout << "The count of " << i.first << " = " << i.second << "\n";
  }



  return 0;
}
