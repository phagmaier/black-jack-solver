#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <utility>
class Player{
public:
  explicit Player(int card1, int card2);
  explicit Player();
  inline void set_cards(std::pair<int,int> &cards){card1=cards.first;card2=cards.second;}
private:
  int card1;
  int card2;
  std::vector<int> dealt;
};

#endif
