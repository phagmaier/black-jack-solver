#include <raylib.h>
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

//FUNCTIONS:
void all_done(int num_decks, std::pair<int,int> &player, int dealer, int *players_dead_cards, int *dealers_dead_cards){
  std::ofstream outputFile("../Data/data.txt"); 
  
  if (outputFile.is_open()) {
    outputFile << num_decks << "\n";

    outputFile << player.first << "\n";

    outputFile << player.second << "\n";

    outputFile << dealer << "\n";

    for (int i = 0; i<NUM_CARDS-1;++i){
      outputFile << i+1 << " " << players_dead_cards[i] << "\n";
    }

    outputFile << 10 <<  players_dead_cards[9] << "\n";

    for (int i = 0; i<NUM_CARDS;++i){
      outputFile << i+1 << " " << dealers_dead_cards[i] << "\n";
    }
    outputFile << 10 << dealers_dead_cards[9] << "\n";
    
    outputFile.close();
  } 
  
  else {
    std::cerr << "ERROR OPENING FILE.\n";
    return;
  }
}

void check_dead(Vector2 &pos, Rectangle *rec1, Rectangle *rec2, 
                std::pair<int,int> &card_clicked, 
                bool &clicked, Rectangle &done, bool &is_done){

  if (CheckCollisionPointRec(pos,done)){
    is_done = true;
    return;
  }
  for (int i=0; i<NUM_CARDS;++i){
    if (CheckCollisionPointRec(pos,rec1[i])){
      clicked=true;
      card_clicked.first = 0;
      card_clicked.second = i;
      //bools1[i] = true;
      return;
    }

    if (CheckCollisionPointRec(pos,rec2[i])){
      clicked=true;
      card_clicked.first = 1;
      card_clicked.second = i;
      //bools2[i] = true;
      return;
    }
 
  }
  clicked = false;
  card_clicked = {-1,-1};
}

void init_dead_cards(Rectangle *recs1, Rectangle *recs2, int *counts1, int *counts2, std::string *strs1, std::string *strs2){
  for (int i=0;i<NUM_CARDS;++i){
    counts1[i] = 0;
    counts2[i] = 0;
    strs1[i] = "0";
    strs2[i] = "0";
  }
  const int total_cards = NUM_CARDS *2; //each side gets 20 cards
  const int num_rows = 2;
  const int num_cols = 5;
  const int padding = 30; //space between dealer and player cards
  const int space = 10;
  const int grid_y_start = 100;
  const int grid_y_end = static_cast<int>((2.0 / 3.0) * WINDOW_HEIGHT);
  const int grid_height = grid_y_end - grid_y_start;
  //const int grid_height = WINDOW_HEIGHT - start_grid_y - (WINDOW_HEIGHT - end_grid_y);

  const int c_w = ((WINDOW_WIDTH-padding) - num_cols*2 * space) / (num_cols*2);
  const int c_h = (grid_height - (num_rows + 1) * space) / num_rows;
  int count = 0;
  for (int row=0;row<num_rows;++row){
    for (int col=0;col<num_cols;++col){
      float y = grid_y_start + row * (c_h + space);
      recs1[count] = Rectangle{static_cast<float>(c_w * col + space * (col+1)), y, c_w, c_h};
      recs2[count] = Rectangle{static_cast<float>(c_w * col + space * (col)) + num_cols * (c_w + space) + padding, y, c_w, c_h};
      ++count;
    }
  }
}

void draw_dead_cards(Rectangle *recs1, Rectangle *recs2, Font &font, std::pair<int,int> &card_selected, std::string *strs1, std::string *strs2){
  static const char *chars[NUM_CARDS] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T"};
  Rectangle tmp;
  Color color;
  for (int i=0;i<NUM_CARDS;++i){
    tmp = recs1[i];
    color = card_selected.first==0 && card_selected.second ==i  ? YELLOW : LIGHTGRAY;
    DrawRectangleLines(tmp.x,tmp.y,tmp.width,tmp.height,BLACK);
    DrawRectangle(tmp.x,tmp.y,tmp.width,tmp.height,color);
    DrawTextEx(font, chars[i],{tmp.x,tmp.y},40,SPACING,BLUE);
    DrawTextEx(font,"ENTER #:",{tmp.x,tmp.y+tmp.width -10},20,SPACING,BLUE);
    DrawTextEx(font, strs1[i].c_str(),{tmp.x+40,tmp.y+150},40,SPACING,RED);

    tmp = recs2[i];
    color = card_selected.first==1 && card_selected.second ==i  ? YELLOW : LIGHTGRAY;
    DrawRectangleLines(tmp.x,tmp.y,tmp.width,tmp.height,BLACK);
    DrawRectangle(tmp.x,tmp.y,tmp.width,tmp.height,color);
    DrawTextEx(font, chars[i],{tmp.x,tmp.y},40,SPACING,BLUE);
    DrawTextEx(font,"ENTER #:",{tmp.x,tmp.y+tmp.width -10},20,SPACING,BLUE);
    DrawTextEx(font, strs2[i].c_str(),{tmp.x+40,tmp.y+150},40,SPACING,RED);
  }
}

void draw_centered_text(const Rectangle &rec, const char * card, int font_size, Font &font){
  int y = rec.y + rec.height / 2.0f - font_size / 2.0f;
  //int text_width = MeasureText(card, font_size);
  int text_width = MeasureTextEx(font,card,font_size,SPACING).x;
  int x = rec.x + (rec.width - text_width) / 2.0f;
  DrawTextEx(font, card, {static_cast<float>(x),static_cast<float>(y)}, font_size, SPACING, BLUE);
}

std::unordered_map<int, const char *> get_dic() {
  const char *chars[NUM_CARDS] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T"};
  std::unordered_map<int, const char *> dic;

  int count = 0;
  for (int i = 0; i < 2; ++i) {
    for (int card = 0; card < NUM_CARDS; ++card) {
      dic[count] = chars[card];
      ++count;
    }
  }
  return dic;
}

void init_cads(Rectangle *p, Rectangle *d, bool *bools_p, bool *bools_d){
  for (int i=0;i<NUM_CARDS*2; ++i){
    bools_p[i] = false;
    bools_d[i] = false;
  }
  const int total_cards = NUM_CARDS *4; //each side gets 20 cards
  const int num_rows = 4;
  const int num_cols = 5;
  const int padding = 30; //space between dealer and player cards
  const int space = 10;
  //const int start_grid_y = 50;
  //const int end_grid_y = WINDOW_HEIGHT -300;
  const int grid_y_start = 100;
  const int grid_y_end = static_cast<int>((2.0 / 3.0) * WINDOW_HEIGHT);
  const int grid_height = grid_y_end - grid_y_start;
  //const int grid_height = WINDOW_HEIGHT - start_grid_y - (WINDOW_HEIGHT - end_grid_y);

  const int c_w = ((WINDOW_WIDTH-padding) - num_cols*2 * space) / (num_cols*2);
  const int c_h = (grid_height - (num_rows + 1) * space) / num_rows;
  int count = 0;
  for (int row=0;row<num_rows;++row){
    for (int col=0;col<num_cols;++col){
      float y = grid_y_start + row * (c_h + space);
      p[count] = Rectangle{static_cast<float>(c_w * col + space * (col+1)), y, c_w, c_h};
      d[count] = Rectangle{static_cast<float>(c_w * col + space * (col)) + num_cols * (c_w + space) + padding, y, c_w, c_h};
      ++count;
    }
  }
}


void draw_card(const Rectangle &rec, const bool clicked, const char *card,Font &font){
  int font_size = 40;
  Color color = clicked ? YELLOW : LIGHTGRAY;
  DrawRectangleLines(rec.x,rec.y,rec.width,rec.height, BLACK);
  DrawRectangle(rec.x,rec.y,rec.width,rec.height, color);
  draw_centered_text(rec, card, font_size,font);
}

void display_card_grid(const Rectangle *p, const Rectangle *d, const bool *bool_p, const bool *bool_d, std::unordered_map<int,const char *> &dic,Font &font){
  int total_cards = NUM_CARDS * 2;
  Color color;
  Rectangle tmp;
  for (int i=0;i<total_cards;++i){
    draw_card(p[i], bool_p[i],dic[i],font);
    draw_card(d[i], bool_d[i],dic[i],font);
  }
}


void draw_header(Rectangle &rec1, Rectangle &rec2, Font &font){
  int font_size = 40;
  float y = rec1.y/2;
  int text_width1 = MeasureTextEx(font,"SELECT PLAYER'S CARDS", font_size,SPACING).x;
  int text_width2 = MeasureTextEx(font, "SELECT DEALER'S CARD", font_size, SPACING).x;
  float x1 = ((rec1.width + rec1.x) - text_width1) / 2.0f;
   DrawTextEx(font, "SELECT PLAYER'S CARDS", {x1,y}, font_size, 2, BLACK);
  DrawTextEx(font, "SELECT DEALER'S CARD", {rec2.x+80,y}, font_size, 2, BLACK);
}


void draw_decks_button(Rectangle &rec, bool clicked, std::string &str, int &count, Font &font){
  int font_size = 35;
  Color line_color = clicked ? YELLOW : DARKGRAY;
  DrawRectangleLines(rec.x,rec.y,rec.width,rec.height, line_color);
  DrawRectangle(rec.x,rec.y,rec.width,rec.height, LIGHTGRAY);
  int text_width = MeasureTextEx(font,"ENTER THE NUMBER OF DECKS:", font_size,SPACING).x;
  float x = rec.x - (text_width +20);
  float y = rec.y+rec.height/2 - 10;
  DrawTextEx(font, "ENTER THE NUMBER OF DECKS:", {x,y}, font_size, SPACING, BLACK);
  if (!str.size() && count >=60){
    DrawTextEx(font,"_", {rec.x+10,y},font_size,SPACING,RED);
  }
  else{
    DrawTextEx(font,str.c_str(), {rec.x+10, rec.y+10}, font_size+10,SPACING,RED);
  }
  count += count == 70 ? -70 : 1;
}


Rectangle create_num_decks_button(){
  const int width = 75;
  const int height = 60;
  const int x = WINDOW_WIDTH/2 - width/2;
  const int y = WINDOW_HEIGHT - 250;
  return Rectangle{x,y,width,height};
}

void draw_done_button(Rectangle &rec, bool able_to_end, Font &font){
  const int font_size = 40;
  Color line_color = able_to_end ? YELLOW : DARKGRAY;
  DrawRectangleLines(rec.x,rec.y,rec.width,rec.height, line_color);
  DrawRectangle(rec.x,rec.y,rec.width,rec.height, LIGHTGRAY);
  //DrawText("DONE",rec.x+10,rec.y+20,40,MAROON);
  DrawTextEx(font,"DONE",{rec.x+10,rec.y+20},font_size,SPACING,MAROON);
}

Rectangle create_done_button(){
  const int width = 135;
  const int height = 75;
  const int x = WINDOW_WIDTH/2 - width/2;
  const int y = WINDOW_HEIGHT - 100;
  return Rectangle{x,y,width,height};
}


void handle_collision_player(const Rectangle &rec, bool &clicked, std::pair<int,int> &hand, int i){
  if (clicked){
    clicked = false;
    hand.first = hand.first == i ? -1 : hand.first; 
    hand.second= hand.second == i ? -1 : hand.second; 
    return;
  }
  if (hand.first == -1){
    hand.first = i;
    clicked = true;
    return;
  }
  if (hand.second == -1){
    hand.second = i;
    clicked = true;
    return;
  }
}


void handle_collision_dealer(const Rectangle &rec, bool &clicked, int &hand, int i){
  if (clicked){
    clicked = false;
    hand = -1;
    return;
  }
  if (hand== -1){
    hand = i;
    clicked = true;
    return;
  }
}


void check_click(const Vector2 &pos, const Rectangle *p, const Rectangle *d, bool *bool_p, 
                 bool *bool_d, const Rectangle &decks, const Rectangle &done, 
                 bool &bool_decks, bool &bool_done, std::pair<int,int>&p1_hand, int &dealer_hand, const int num_decks, Function_choice &func){
  
  if (CheckCollisionPointRec(pos,decks)){
    bool_decks = true;
    return;
  }
  
  if (CheckCollisionPointRec(pos,done)){
    bool_done = p1_hand.first !=-1 && p1_hand.second !=-1 && dealer_hand != -1 && num_decks > 0;
    func = bool_done ? DEAD : func;
    return;
  }

  bool_decks = false;
  for (int i=0;i<NUM_CARDS*2;++i){
    if (CheckCollisionPointRec(pos,p[i])){
      handle_collision_player(p[i],bool_p[i],p1_hand,i); 
      return;
    }
    if (CheckCollisionPointRec(pos,d[i])){
      handle_collision_dealer(d[i],bool_d[i],dealer_hand,i); 
      return;
    }
  }
}


void get_num_cards(std::string &str) {
  if (IsKeyPressed(KEY_BACKSPACE) && !str.empty()) {
    str.pop_back();  
    if (!str.size()){
      str = "0";
    }
    return;  
  }

  int key = GetCharPressed();
  if (key >= '0' && key <= '9' && str.size() < 3) {  
  if (str != "0"){
    str.push_back(static_cast<char>(key));         
  }
  else{
    str = static_cast<char>(key);
  }
    }
  if (str.empty()) {
    str = "0";  
  }
}


void draw_number_decks(std::string &str){
  int key = GetCharPressed();
  while (key > 0) {
    if ((key >= '0' && key <= '9') && str.size() < 5) {
      std::string tmp = str;
      tmp.push_back(char(key));
      int tmp_num = std::stoi(tmp);
      if (tmp_num > 0 && tmp_num <11){
        str.push_back((char)key);
      }
    }
    key = GetCharPressed();
  }
  if (IsKeyPressed(KEY_BACKSPACE) && !str.empty()) {
    str.pop_back();
  }
}


void start_func(Rectangle *player_Recs, Rectangle *dealer_Recs, bool *player_clicked, 
                     bool *dealer_clicked, Rectangle &num_decks_rec, std::string &num_decks_str,
                     int &count, bool &clicked_num_decks, std::pair<int,int> &player_hand, 
                     int &dealer_hand, Rectangle &done_rec, bool &clicked_done, 
                     Font &font40, Font &font30, std::unordered_map<int,const char *> &dic, Function_choice &func){

  if (clicked_num_decks){
    draw_number_decks(num_decks_str);
  }

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 pos= GetMousePosition();
    check_click(pos,player_Recs,dealer_Recs,player_clicked,dealer_clicked,
                num_decks_rec,done_rec,clicked_num_decks,
                clicked_done,player_hand,dealer_hand,
                num_decks_str.size(), func);
  }

  draw_header(player_Recs[4], dealer_Recs[0],font40);
  display_card_grid(player_Recs,dealer_Recs,player_clicked,dealer_clicked, dic,font40);
  draw_decks_button(num_decks_rec, false, num_decks_str, count,font30);
  draw_done_button(done_rec,false,font40);
}

void dead_func(Rectangle *dead_Recs1, Rectangle *dead_Recs2, int *counts1,
               int *counts2, std::string *dead_strs1, std::string *dead_strs2,
               Rectangle &dead_done_rec, std::pair<int,int> &card_clicked,
               bool &get_input, bool &dead_done, Font &font40, 
               Font &font30, std::pair<int,int> &player_hand, int &dealer_hand, 
               std::string &num_decks_str,Function_choice &func){
  
  /* //Don't think i need this
  if (IsKeyPressed(KEY_ESCAPE)) {
    CloseWindow();
    return 0;
  }
  */
  if (!dead_done){
    if (get_input){
      if (card_clicked.first == 0){
        get_num_cards(dead_strs1[card_clicked.second]);
        counts1[card_clicked.second] = std::stoi(dead_strs1[card_clicked.second]);
      }
      else{
        get_num_cards(dead_strs2[card_clicked.second]);
        counts2[card_clicked.second] = std::stoi(dead_strs2[card_clicked.second]);
      }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 pos= GetMousePosition();
      check_dead(pos,dead_Recs1,dead_Recs2,card_clicked,get_input,dead_done_rec,dead_done);
    }
    draw_dead_cards(dead_Recs1,dead_Recs2,font40, card_clicked,dead_strs1, dead_strs2);
    draw_done_button(dead_done_rec, true, font40);
  }
  else{
    
    std::pair<int,int> new_player = {player_hand.first%10+1,player_hand.second%10+1};
    int new_dealer= dealer_hand%10+1;
    all_done(std::stoi(num_decks_str),new_player,new_dealer,counts1,counts2);
    func = DISPLAY;
  }

}





int main(){
  //INIT VARIABLES
  std::unordered_map<int,const char *> dic = get_dic();
  Rectangle player_Recs[NUM_CARDS*2];
  Rectangle dealer_Recs[NUM_CARDS*2];
  bool player_clicked[NUM_CARDS*2];
  bool dealer_clicked[NUM_CARDS*2];
  init_cads(player_Recs, dealer_Recs, player_clicked, dealer_clicked);
  Rectangle num_decks_rec = create_num_decks_button();
  std::string num_decks_str = "";
  int count = 0;
  bool clicked_num_decks = false;
  std::pair<int,int> player_hand = {-1,-1};
  int dealer_hand = -1;

  Rectangle done_rec = create_done_button();
  bool clicked_done= false;

  //FOR THE SECOND PART WHERE YOU GET DEAD CARDS
  Rectangle dead_Recs1[NUM_CARDS*2];
  Rectangle dead_Recs2[NUM_CARDS*2];
  //bool dead_clicked1[NUM_CARDS*2];
  //bool dead_clicked2[NUM_CARDS*2];
  int counts1[NUM_CARDS];
  int counts2[NUM_CARDS];

  std::string dead_strs1[NUM_CARDS];
  std::string dead_strs2[NUM_CARDS];

  init_dead_cards(dead_Recs1,dead_Recs2,counts1,counts2, dead_strs1, dead_strs2);
  Rectangle dead_done_rec = create_done_button();

  std::pair<int,int> card_clicked = {-1,-1};
  bool get_input = false;
  bool dead_done = false;

  Function_choice func = START;


  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BLACKJACK");
  SetTargetFPS(60);

  Font font30= LoadFontEx("../Font/OpenSans-Bold.ttf", 35, nullptr, 250);
  Font font40= LoadFontEx("../Font/Roboto-Medium.ttf", 40, nullptr, 250);

  
  
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (func==START){
      start_func(player_Recs, dealer_Recs, player_clicked, 
                 dealer_clicked, num_decks_rec, num_decks_str,
                 count, clicked_num_decks, player_hand, 
                 dealer_hand, done_rec, clicked_done, 
                 font40, font30, dic,func);
    }
    else if(func==DEAD){
      dead_func(dead_Recs1, dead_Recs2, counts1,
               counts2, dead_strs1, dead_strs2,
               dead_done_rec, card_clicked,
               get_input, dead_done, font40, 
               font30, player_hand, dealer_hand, 
               num_decks_str,func);
    }
    else if(func == HIT){
      std::cout << "Haven't implimented this \n"
        << "I envision it will just be a screen that displays a grid of cards\n"
        <<"with a done button you can press so you can select what card you got\n"
        << "When you hit\n";
      EndDrawing();
      break;
    }
    else if(func == DISPLAY){
      std::cout << "NOT IMPLIMETED YET IT WILL JUST SHOW THE BEST ACTION TO TAKE\n"
      <<"AS WELL AS THE PERCETNAGES OF THE DEALER AND PLAYER GETTING CERTAIN HANDS I GUESS\n";
      EndDrawing();
      break;

    }
    else{
      EndDrawing();
      break;
    }
    EndDrawing();
  }



  return 0;
}
