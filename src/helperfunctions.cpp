#include "helperfunctions.h"

std::unordered_map<int, float> get_percentages(std::unordered_map<int, int>& prct){
  std::cout << "------------------------------------------------------------------\n";
  std::cout << "PERCENTAGES\n";
  std::cout << "------------------------------------------------------------------\n";
  static std::unordered_map<int,int> dic = {{-1,0},{17,1},{18,2},{19,3},{20,4},{21,5}};
  float odds[6] = {0,0,0,0,0,0};
  std::unordered_map<int, float> results;
  float total = 0;
  for (auto& i : prct) {
    total += i.second;
    //std::cout << i.first << ": " << i.second << "\n";
  }
  float temp;
  for (auto& [key,val] : prct) {
    temp =  (float)val / total;
    results[key] = temp;
    odds[dic[key]] = temp * 100;
  } 
  
  std::cout << "Chance the dealer BUSTS: " << odds[0] << "%\n";
  std::cout << "------------------------------------------------------------------\n";
  for (int i=17;i<22;++i){
    std::cout << "CHACE the Dealer hits " << i << ": " << odds[dic[i]] << "%\n";
    std::cout << "------------------------------------------------------------------\n";
  } 
  std::cout << "\n";
  return results;
}

void print_cum_prob(std::unordered_map<int,float> &prcts){
  float cum_prob = 0;
  std::cout << "---------------------------------------\n";
  std::cout << "CUMULATIVE RESULTS\n";
  std::cout << "---------------------------------------\n";
  float total = 0;
  cum_prob += prcts[-1];
  std::cout << "The chances of you winning if you just don't BUST: " << cum_prob *100 << "%\n";
  std::cout << "------------------------------------------------------------------\n";
  cum_prob += prcts[17];
  std::cout << "The chances of you winning or pushing if you get to 17: " << cum_prob* 100 << "%\n";
  std::cout << "------------------------------------------------------------------\n";
  cum_prob += prcts[18];
  std::cout << "The chances of you winning or pushing if you get to 18: " << cum_prob * 100 << "%\n";
  std::cout << "------------------------------------------------------------------\n";
  cum_prob += prcts[19];
  std::cout << "The chances of you winning or pushing if you get to 19: " << cum_prob * 100 << "%\n";
  std::cout << "------------------------------------------------------------------\n";
  cum_prob += prcts[20];
  std::cout << "The chances of you winning or pushing if you get to 20: " << cum_prob * 100 << "%\n";
  std::cout << "------------------------------------------------------------------\n";
  cum_prob += prcts[21];
  std::cout << "The chances of you winning or pushing if you get to 21: " << cum_prob * 100 << "%\n";
  std::cout << "------------------------------------------------------------------\n";
}


int get_num_decks()
{
    std::string deck_string = "";
    int num_decks;
    std::cout << "Enter the number of decks used: ";
    std::cin >> deck_string;
    std::cout << "\n";

    while (!is_int(deck_string)) {
        deck_string = "";
        std::cout << "I'm Sorry that was not a valid entry\n";
        std::cout << "Please enter the number of decks used: ";
        std::cin >> deck_string;
        std::cout << "\n";
    }
    num_decks = std::stoi(deck_string);
    return num_decks;
}

int get_card_val()
{
    std::string card = "";
    std::cout << "Please enter the card: ";
    std::cin >> card;
    while (VALID_VALS.find(card) == VALID_VALS.end()) {
        card = "";
        std::cout << "I'm Sorry that was not a valid entry\n";
        std::cout << "Please enter the card: ";
        std::cin >> card;
        std::cout << "\n";
    }
    auto it = VAL_DIC.find(card);
    if (it != VAL_DIC.end()) {
        return it->second;
    } else {
        std::cerr << "ERROR INVALID CARD ENTERED\n";
        std::cerr << "THE STRING ENTERED WAS: " << card << "\n";
        return -1;
    }
}

void get_dealers_hand(int& dealer)
{
    std::cout << "-----------------------\n";
    std::cout << "Please Enter the card the dealer is showing\n";
    dealer = get_card_val();
}

void get_players_hand(std::pair<int, int>& player)
{
    std::cout << "-----------------------\n";
    std::cout << "FIRST CARD\n";
    player.first = get_card_val();
    std::cout << "-----------------------\n";
    std::cout << "SECOND CARD\n";
    player.second = get_card_val();
}

void make_deck(std::unordered_map<int, int>& deck, int num_decks, std::pair<int, int>& hand, int dealer)
{
    for (int i = 1; i < 10; ++i) {
        deck[i] = 4 * num_decks;
    }
    // 10 jack king queen all == 10
    deck[10] = 4 * 4 * num_decks;
    deck[dealer] -= 1;
    deck[hand.first] -= 1;
    deck[hand.second] -= 1;

    if (deck[dealer] < 0 || deck[hand.first] < 0 || deck[hand.second] < 0) {
        std::cerr << "Impossible hand dealt too many dealt cards of a particular type";
        return;
    }
}

void set_21_payout(std::pair<int, int>& fraction)
{
    int choice = 0;
    std::cout << "What is the payout for a BLACKJACK\n";
    std::cout << "1: 3:2\n";
    std::cout << "2: 6:5\n";
    std::cout << "Please Select either 1 or 2: ";
    std::cin >> choice;
    std::cout << "\n";
    while (choice != 1 && choice != 2) {
        choice = 0;
        std::cout << "I'm sorry that wasn't a valid\n";
        std::cout << "What is the payout for a BLACKJACK\n";
        std::cout << "1: 3:2\n";
        std::cout << "2: 6:5\n";
        std::cout << "Please Select either 1 or 2: ";
        std::cin >> choice;
        std::cout << "\n";
    }

    if (choice == 1) {
        fraction = { 3, 2 };
    } else {
        fraction = { 6, 5 };
    }
    return;
}

void get_dead_cards(std::unordered_map<int, int>& deck)
{
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
    }
}

// should do this when making deck and update when
// other cards are considered but for now it's fine
int get_deck_size(std::unordered_map<int, int>& deck)
{
    int size = 0;
    for (auto& i : deck) {
        size += i.second;
    }
    return size;
}

float get_blackJack_payout(float bet, std::pair<int,int> &fraction){
  bet *= (float)fraction.first;
  return bet / (float)fraction.second;

}

std::vector<int> make_deck_vector(std::unordered_map<int,int> &dic){
  std::vector<int> deck;
  for (auto &i : dic){
    for (int x=0;x<i.second;++x){
      deck.push_back(i.first);
    }
  }
  return deck;
}

//bool because we are assuming dealer doesn't have 21 
//if you are looking at optimal strat to take
int get_random_card(std::vector<int>& vec, bool second_card) {
  static std::random_device rd;     // Static to initialize only once
  static std::mt19937 gen(rd());    // Static random engine
  static std::uniform_int_distribution<> dis; // Static distribution

  if (vec.empty()) {
    throw std::runtime_error("Vector is empty. Cannot get a random value.");
  }

  int index, num;
  do {
    dis.param(std::uniform_int_distribution<>::param_type(0, vec.size() - 1)); // Adjust range
    index = dis(gen);
    num = vec[index];
  } while (second_card && num == 1); 

  vec[index] = vec.back(); 
  vec.pop_back();          

  return num;
}

int get_best_val(int regular, int ace){
  if (ace >= 17 && ace < 22){
    return ace;
  }
  return regular;
}

TRIPLE get_dealer_action(int regular, int ace){
  if (regular > 21){
    return BUST;
  }
  if ((ace >= 17 && ace < 22) || (regular >=17 && regular < 22)){
    return STAY;
  }
  return HIT;
}

void get_sum(int &reg_sum, int &ace_sum, int card, bool &ace){
  if (ace){
    ace_sum += card;
  }
  else if (card == 1){
    ace = true;
    ace_sum +=11;
  }
  else{
    ace_sum += card;
  }
  reg_sum += card;
}

int hit(std::vector<int> &deck, int reg_sum, int ace_sum, bool ace, std::vector<int> &discarded){
  TRIPLE action = HIT;
  while (action == HIT){
    int card = get_random_card(deck,false);
    discarded.push_back(card);
    get_sum(reg_sum,ace_sum,card,ace);
    action = get_dealer_action(reg_sum,ace_sum);
  }
  if (action == BUST){
    return -1;
  }
  return get_best_val(reg_sum,ace_sum);
}

int decision(TRIPLE action, std::vector<int> &deck, int reg_sum, int ace_sum, bool ace, std::vector<int> &discarded){
  if (action == BUST){
    return -1;
  }
  if (action == STAY){
    return get_best_val(reg_sum, ace_sum);
  }
  return hit(deck, reg_sum,ace_sum,ace,discarded);
}

std::unordered_map<int,int> simulation(std::unordered_map<int,int> &dic_deck, int dealer_card1, std::pair<int,int> &player){
  std::unordered_map<int,int> result;
  std::vector<int> deck = make_deck_vector(dic_deck);
  bool ace = dealer_card1 == 1 ? true : false;
  TRIPLE action;
  for (int i=0; i < ITERATIONS; ++i){
    int dealer_sum = dealer_card1;
    int ace_dealer_sum = ace ? 11 : dealer_card1;
    std::vector<int> discarded;
    int dealer_card2 = get_random_card(deck,true);
    discarded.push_back(dealer_card2);
    get_sum(dealer_sum, ace_dealer_sum, dealer_card2,ace);
    action = get_dealer_action(dealer_sum, ace_dealer_sum);
    result[decision(action, deck, dealer_sum, ace_dealer_sum, ace, discarded)] +=1; 
    for (int i: discarded){
      deck.push_back(i);
    }

  } 
    return result;
}


// Need to add something where if you want to you can also pick up up from after you've hit
// so you can burn extra cards
void start_game(std::unordered_map<int, int>& deck, int& dealer, std::pair<int, int>& payout){
  std::cout << "BLACKJACK SOLVER. PLEASE FOLLOW THE INSTRUCTIONS ON THE SCREEN AND ENTER CARD INFORMATION\n";
  std::cout << "---------------------------------------\n";
  int num_decks = get_num_decks();
  std::pair<int, int> player;
  get_players_hand(player);
  get_dealers_hand(dealer);
  make_deck(deck, num_decks, player, dealer);
  set_21_payout(payout);
  //p1.set_cards(player);
  get_dead_cards(deck);
  std::unordered_map<int,int> results = simulation(deck, dealer, player);
  std::unordered_map<int,float> prcts = get_percentages(results);
  print_cum_prob(prcts); 
}
