#include "Gui.h"

Gui::Gui(){
  dic = get_dic();
  init_cards();
  num_decks_rec = create_num_decks_button();
  num_decks_str = "";
  count = 0;
  clicked_num_decks = false;
  player_hand = {-1,-1};
  dealer_hand = -1;
  done_rec = create_done_button();
  clicked_done = false;
  init_dead_cards();
  dead_done_rec = create_done_button();
  card_clicked = {-1,-1};
  get_input = false;
  dead_done = false;
  func = START;
}


void Gui::all_done(){
  player_hand.first = player_hand.first %10 +1;
  player_hand.second= player_hand.second %10 +1;
  dealer_hand = dealer_hand % 10 + 1;

  std::ofstream outputFile("../Data/data.txt"); 
  
  if (outputFile.is_open()) {
    outputFile << num_decks_str << "\n";

    outputFile << player_hand.first << "\n";

    outputFile << player_hand.second << "\n";

    outputFile << dealer_hand << "\n";

    for (int i = 0; i<NUM_CARDS;++i){
      outputFile << i+1 << " " << dead_strs1[i] << "\n";
    }

    for (int i = 0; i<NUM_CARDS-1;++i){
      outputFile << i+1 << " " << dead_strs2[i] << "\n";
    }
    outputFile << 10 << " " << dead_strs2[9] << "\n";
    
    outputFile.close();
  } 
  
  else {
    std::cerr << "ERROR OPENING FILE.\n";
    return;
  }
}

void Gui::init_cards(){
  for (int i=0;i<NUM_CARDS*2; ++i){
    player_clicked[i] = false;
    dealer_clicked[i] = false;
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
      player_Recs[count] = Rectangle{static_cast<float>(c_w * col + space * (col+1)), y, c_w, c_h};
      dealer_Recs[count] = Rectangle{static_cast<float>(c_w * col + space * (col)) + num_cols * (c_w + space) + padding, y, c_w, c_h};
      ++count;
    }
  }
}


void Gui::check_dead(Vector2 &pos){

  if (CheckCollisionPointRec(pos, dead_done_rec)){
    dead_done= true;
    return;
  }
  for (int i=0; i<NUM_CARDS;++i){
    if (CheckCollisionPointRec(pos,dead_Recs1[i])){
      get_input=true;
      card_clicked.first = 0;
      card_clicked.second = i;
      //bools1[i] = true;
      return;
    }

    if (CheckCollisionPointRec(pos,dead_Recs2[i])){
      get_input=true;
      card_clicked.first = 1;
      card_clicked.second = i;
      //bools2[i] = true;
      return;
    }
 
  }
  get_input= false;
  card_clicked = {-1,-1};
}


void Gui::init_dead_cards(){
  for (int i=0;i<NUM_CARDS;++i){
    counts1[i] = 0;
    counts2[i] = 0;
    dead_strs1[i] = "0";
    dead_strs2[i] = "0";
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
      dead_Recs1[count] = Rectangle{static_cast<float>(c_w * col + space * (col+1)), y, c_w, c_h};
      dead_Recs2[count] = Rectangle{static_cast<float>(c_w * col + space * (col)) + num_cols * (c_w + space) + padding, y, c_w, c_h};
      ++count;
    }
  }
}


void Gui::draw_dead_cards(){
  static const char *chars[NUM_CARDS] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T"};
  Rectangle tmp;
  Color color;
  for (int i=0;i<NUM_CARDS;++i){
    tmp = dead_Recs1[i];
    color = card_clicked.first==0 && card_clicked.second ==i  ? YELLOW : LIGHTGRAY;
    DrawRectangleLines(tmp.x,tmp.y,tmp.width,tmp.height,BLACK);
    DrawRectangle(tmp.x,tmp.y,tmp.width,tmp.height,color);
    DrawTextEx(font40, chars[i],{tmp.x,tmp.y},40,SPACING,BLUE);
    DrawTextEx(font40,"ENTER #:",{tmp.x,tmp.y+tmp.width -10},20,SPACING,BLUE);
    DrawTextEx(font40, dead_strs1[i].c_str(),{tmp.x+40,tmp.y+150},40,SPACING,RED);

    tmp = dead_Recs2[i];
    color = card_clicked.first==1 && card_clicked.second ==i  ? YELLOW : LIGHTGRAY;
    DrawRectangleLines(tmp.x,tmp.y,tmp.width,tmp.height,BLACK);
    DrawRectangle(tmp.x,tmp.y,tmp.width,tmp.height,color);
    DrawTextEx(font40, chars[i],{tmp.x,tmp.y},40,SPACING,BLUE);
    DrawTextEx(font40,"ENTER #:",{tmp.x,tmp.y+tmp.width -10},20,SPACING,BLUE);
    DrawTextEx(font40, dead_strs2[i].c_str(),{tmp.x+40,tmp.y+150},40,SPACING,RED);
  }
}


void Gui::draw_centered_text(const Rectangle &rec, const char * card){
  const static int font_size = 40;
  int y = rec.y + rec.height / 2.0f - font_size / 2.0f;
  //int text_width = MeasureText(card, font_size);
  int text_width = MeasureTextEx(font40,card,font_size,SPACING).x;
  int x = rec.x + (rec.width - text_width) / 2.0f;
  DrawTextEx(font40, card, {static_cast<float>(x),static_cast<float>(y)}, font_size, SPACING, BLUE);
}

std::unordered_map<int, const char *> Gui::get_dic() {
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


void Gui::draw_card(const Rectangle &rec, const bool clicked, const char *card){
  //const static int font_size = 40;
  Color color = clicked ? YELLOW : LIGHTGRAY;
  DrawRectangleLines(rec.x,rec.y,rec.width,rec.height, BLACK);
  DrawRectangle(rec.x,rec.y,rec.width,rec.height, color);
  draw_centered_text(rec, card);
}


void Gui::draw_header(Rectangle &rec1, Rectangle &rec2){
  const static int font_size = 40;
  float y = rec1.y/2;
  int text_width1 = MeasureTextEx(font40,"SELECT PLAYER'S CARDS", font_size,SPACING).x;
  int text_width2 = MeasureTextEx(font40, "SELECT DEALER'S CARD", font_size, SPACING).x;
  float x1 = ((rec1.width + rec1.x) - text_width1) / 2.0f;
  DrawTextEx(font40, "SELECT PLAYER'S CARDS", {x1,y}, font_size, 2, BLACK);
  DrawTextEx(font40, "SELECT DEALER'S CARD", {rec2.x+80,y}, font_size, 2, BLACK);
}


void Gui::draw_decks_button(){
  int font_size = 35;
  // can add functionality where it changes color when it can be clicked
  //Color line_color = clicked ? YELLOW : DARKGRAY;   
  Color line_color = DARKGRAY;
  DrawRectangleLines(num_decks_rec.x,num_decks_rec.y,num_decks_rec.width,num_decks_rec.height, line_color);
  DrawRectangle(num_decks_rec.x,num_decks_rec.y,num_decks_rec.width,num_decks_rec.height, LIGHTGRAY);
  int text_width = MeasureTextEx(font30,"ENTER THE NUMBER OF DECKS:", font_size,SPACING).x;
  float x = num_decks_rec.x - (text_width +20);
  float y = num_decks_rec.y+num_decks_rec.height/2 - 10;
  DrawTextEx(font30, "ENTER THE NUMBER OF DECKS:", {x,y}, font_size, SPACING, BLACK);
  if (!num_decks_str.size() && count >=60){
    DrawTextEx(font30,"_", {num_decks_rec.x+10,y},font_size,SPACING,RED);
  }
  else{
    DrawTextEx(font30,num_decks_str.c_str(), {num_decks_rec.x+10, num_decks_rec.y+10}, font_size+10,SPACING,RED);
  }
  count += count == 70 ? -70 : 1;
}


Rectangle Gui::create_num_decks_button(){
  const static int width = 75;
  const static int height = 60;
  const static int x = WINDOW_WIDTH/2 - width/2;
  const static int y = WINDOW_HEIGHT - 250;
  return Rectangle{x,y,width,height};
}


void Gui::draw_done_button(bool able_to_end){
  const static int font_size = 40;
  Color line_color = able_to_end ? YELLOW : DARKGRAY;
  DrawRectangleLines(done_rec.x,done_rec.y,done_rec.width,done_rec.height, line_color);
  DrawRectangle(done_rec.x,done_rec.y,done_rec.width,done_rec.height, LIGHTGRAY);
  //DrawText("DONE",rec.x+10,rec.y+20,40,MAROON);
  DrawTextEx(font40,"DONE",{done_rec.x+10,done_rec.y+20},font_size,SPACING,MAROON);
}

void Gui::dead_func(){
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
      check_dead(pos);
    }
    draw_dead_cards();
    draw_done_button(true);
  }
  else{
    
    std::pair<int,int> new_player = {player_hand.first%10+1,player_hand.second%10+1};
    int new_dealer= dealer_hand%10+1;
    all_done();
    func = DISPLAY;
  }
}



void Gui::get_num_cards(std::string &str) {
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


void Gui::display_card_grid(){
  int total_cards = NUM_CARDS * 2;
  Color color;
  Rectangle tmp;
  for (int i=0;i<total_cards;++i){
    draw_card(player_Recs[i], player_clicked[i],dic[i]);
    draw_card(dealer_Recs[i], dealer_clicked[i],dic[i]);
  }
}


Rectangle Gui::create_done_button(){
  const static int width = 135;
  const static int height = 75;
  const static int x = WINDOW_WIDTH/2 - width/2;
  const static int y = WINDOW_HEIGHT - 100;
  return Rectangle{x,y,width,height};
}


void Gui::handle_collision_player(const Rectangle &rec, bool &clicked, int i){
  if (clicked){
    clicked = false;
    player_hand.first = player_hand.first == i ? -1 : player_hand.first; 
    player_hand.second= player_hand.second == i ? -1 : player_hand.second; 
    return;
  }
  if (player_hand.first == -1){
    player_hand.first = i;
    clicked = true;
    return;
  }
  if (player_hand.second == -1){
    player_hand.second = i;
    clicked = true;
    return;
  }
}


void Gui::handle_collision_dealer(const Rectangle &rec, bool &clicked, int i){
  if (clicked){
    clicked = false;
    dealer_hand = -1;
    return;
  }
  if (dealer_hand== -1){
    dealer_hand = i;
    clicked = true;
    return;
  }
}


void Gui::check_click(Vector2 &pos){
  
  if (CheckCollisionPointRec(pos,num_decks_rec)){
    clicked_num_decks= true;
    return;
  }
  
  if (CheckCollisionPointRec(pos,done_rec)){
    clicked_done= player_hand.first !=-1 && player_hand.second !=-1 && dealer_hand != -1 && num_decks_str != "0";
    func = clicked_done ? DEAD : func;
    return;
  }

  clicked_num_decks = false;
  for (int i=0;i<NUM_CARDS*2;++i){
    if (CheckCollisionPointRec(pos,player_Recs[i])){
      handle_collision_player(player_Recs[i],player_clicked[i],i); 
      return;
    }
    if (CheckCollisionPointRec(pos,dealer_Recs[i])){
      handle_collision_dealer(dealer_Recs[i],dealer_clicked[i],i); 
      return;
    }
  }
}

void Gui::draw_number_decks(){
  int key = GetCharPressed();
  while (key > 0) {
    if ((key >= '0' && key <= '9') && num_decks_str.size() < 5) {
      std::string tmp = num_decks_str;
      tmp.push_back(char(key));
      int tmp_num = std::stoi(tmp);
      if (tmp_num > 0 && tmp_num <11){
        num_decks_str.push_back((char)key);
      }
    }
    key = GetCharPressed();
  }
  if (IsKeyPressed(KEY_BACKSPACE) && !num_decks_str.empty()) {
    num_decks_str.pop_back();
  }
}

void Gui::start_func(){
  
  if (clicked_num_decks){
    draw_number_decks();
  }

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 pos= GetMousePosition();
    check_click(pos);
  }

  draw_header(player_Recs[4], dealer_Recs[0]);
  display_card_grid();
  draw_decks_button();
  draw_done_button(false);
}

void Gui::game_loop(){
  
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BLACKJACK");
  SetTargetFPS(60);

  font30= LoadFontEx("../Font/OpenSans-Bold.ttf", 35, nullptr, 250);
  font40= LoadFontEx("../Font/Roboto-Medium.ttf", 40, nullptr, 250);


  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (func==START){
      start_func();
    }
    else if(func==DEAD){
      dead_func();
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
}
