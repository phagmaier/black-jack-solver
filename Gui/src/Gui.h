#ifndef GUI_H
#define GUI_H

#include "raylib.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <fstream>

enum Function_choice{
  START,
  DEAD,
  HIT,
  DISPLAY,
  NOTHING
};


const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;
const int NUM_CARDS = 10;
const int SPACING = 5;

class Gui{
private:
  std::unordered_map<int,const char *> dic;

  Rectangle player_Recs[NUM_CARDS*2];
  Rectangle dealer_Recs[NUM_CARDS*2];
  bool player_clicked[NUM_CARDS*2];
  bool dealer_clicked[NUM_CARDS*2];
  //init_cads(player_Recs, dealer_Recs, player_clicked, dealer_clicked);
  Rectangle num_decks_rec;
  std::string num_decks_str;
  int count = 0;
  bool clicked_num_decks;
  std::pair<int,int> player_hand;
  int dealer_hand;

  Rectangle done_rec;
  bool clicked_done;

  //FOR THE SECOND PART WHERE YOU GET DEAD CARDS
  Rectangle dead_Recs1[NUM_CARDS*2];
  Rectangle dead_Recs2[NUM_CARDS*2];
  int counts1[NUM_CARDS];
  int counts2[NUM_CARDS];

  std::string dead_strs1[NUM_CARDS];
  std::string dead_strs2[NUM_CARDS];

  Rectangle dead_done_rec;

  std::pair<int,int> card_clicked;
  bool get_input;
  bool dead_done;

  Function_choice func;

  Font font30;
  Font font40;
public:
  Gui();
  void all_done(); //done
  void check_dead(Vector2 &pos); //done
  void init_dead_cards();//good
  void draw_dead_cards(); //good
  void draw_centered_text(const Rectangle &rec, const char * card); //good
  std::unordered_map<int, const char *> get_dic(); //good
  void init_cards(); //done
  void draw_card(const Rectangle &rec, const bool clicked, const char *card); //good
  void display_card_grid(); //done
  void draw_header(Rectangle &rec1, Rectangle &rec2); //done
  void draw_decks_button(); //done
  Rectangle create_num_decks_button(); //done
  void draw_done_button(bool able_to_end); //done
  Rectangle create_done_button(); //done
  void handle_collision_player(const Rectangle &rec, bool &clicked, int i); //done
  void handle_collision_dealer(const Rectangle &rec, bool &clicked, int i); //done
  void check_click(Vector2 &pos); //done
  void get_num_cards(std::string &str); //done
  void draw_number_decks(); //done
  void start_func(); //done
  void dead_func(); //done
  void game_loop();

};

#endif
