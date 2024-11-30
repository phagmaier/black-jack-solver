#include "helperfunctions.h"


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



int get_card_val(){
  std::string card = "";
  std::cout << "Please enter the card: ";
  std::cin >> card;
  while (VALID_VALS.find(card) == VALID_VALS.end()){
    card= "";
    std::cout << "I'm Sorry that was not a valid entry\n";
    std::cout << "Please enter the card: ";
    std::cin >> card;
    std::cout << "\n";
  }
  auto it = VAL_DIC.find(card);
  if (it !=VAL_DIC.end()){
    return it->second;
  }
  else{
    std::cerr << "ERROR INVALID CARD ENTERED\n";
    std::cerr << "THE STRING ENTERED WAS: " << card << "\n";
    return -1;
  }
}


void get_dealers_hand(int &dealer){
  std::cout << "-----------------------\n";
  std::cout << "Please Enter the card the dealer is showing\n";
  dealer = get_card_val();
}

void get_players_hand(std::pair<int,int> &player){
  std::cout << "-----------------------\n";
  std::cout << "FIRST CARD\n";
  player.first = get_card_val();
  std::cout << "-----------------------\n";
  std::cout << "SECOND CARD\n";
  player.second= get_card_val();
}

void make_deck(std::unordered_map<int, int> &deck, int num_decks, std::pair<int,int> &hand, int dealer){
  for (int i=0;i<10;++i){
    deck[i] = 4 * num_decks;
  }
  //10 jack king queen all == 10
  deck[10] = 4 * 4 * num_decks;
  deck[dealer] -= 1;
  deck[hand.first] -=1;
  deck[hand.second] -=1;
  
  if (deck[dealer] <0 || deck[hand.first] < 0 || deck[hand.second] < 0){
    std::cerr << "Impossible hand dealt too many dealt cards of a particular type";
    return;
  }
}


void set_21_payout(std::pair<int,int> &fraction){
  int choice=0;
  std::cout << "What is the payout for a BLACKJACK\n";
  std::cout << "1: 3:2\n";
  std::cout << "2: 6:5\n";
  std::cout << "Please Select either 1 or 2: ";
  std::cin >> choice;
  std::cout << "\n";
  while (choice != 1 && choice != 2){
    choice = 0;
    std::cout << "I'm sorry that wasn't a valid\n";
    std::cout << "What is the payout for a BLACKJACK\n";
    std::cout << "1: 3:2\n";
    std::cout << "2: 6:5\n";
    std::cout << "Please Select either 1 or 2: ";
    std::cin >> choice;
    std::cout << "\n";
  }

  if (choice == 1){
    fraction = {3,2};
  }
  else{
    fraction = {6,5};
  }
  return;
}


void get_dead_cards(std::unordered_map<int, int>& deck) {
    std::cout << "---------------------------\n";
    std::cout << "ENTER ANY OTHER DEAD CARDS\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
      std::string input;
      std::cout << "Enter the cards (or press Enter to skip): ";
      std::getline(std::cin, input);
      
      if (input.empty()) {
        return;
      }

      std::istringstream ss(input);
      std::string card;
      std::vector<int> valid_cards;
      bool invalid_input = false;
      
      while (ss >> card) {
        auto it = VAL_DIC.find(card);
        if (it == VAL_DIC.end()) {
          std::cout << "Invalid card: " << card << ". Please try again.\n";
          invalid_input = true;  
          break;  
        }
        valid_cards.push_back(it->second);  
      }
      if (invalid_input) {
        continue;
      }
      for (int card : valid_cards) {
        std::cout << "DELETING " << card << "\n";
        deck[card] -= 1;  
      }
      return; 
    }
}


//Need to add something where if you want to you can also pick up up from after you've hit 
//so you can burn extra cards
void start_game(std::unordered_map<int,int> &deck, int &dealer, std::pair<int,int> &payout, Player &p1){
  std::cout << "BLACKJACK SOLVER. PLEASE FOLLOW THE INSTRUCTIONS ON THE SCREEN AND ENTER CARD INFORMATION\n";
  std::cout << "---------------------------------------\n";
  int num_decks = get_num_decks();
  std::pair<int,int> player;
  get_players_hand(player);
  get_dealers_hand(dealer);
  make_deck(deck, num_decks, player, dealer);
  set_21_payout(payout);
  p1.set_cards(player);
  get_dead_cards(deck);
}
