#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>

// Constants for UI scaling
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

const int CARD_COLUMNS = 6;
const int CARD_ROWS = 4;


void write_to_file(std::pair<int,int> &player, int dealer, int num_decks, std::vector<int> &dead_cards){
  std::ofstream outfile;
  outfile.open("cardData.txt", std::ios::out); 
  outfile << player.first << "\n";
  outfile << player.second << "\n";
  outfile << dealer << "\n";
  outfile << num_decks << "\n";
  for (int card : dead_cards){
    outfile << card << "\n";
  }
  outfile << -1 << "\n";
}

void draw_possible_cards(std::vector<Rectangle> &cards, std::vector<bool> &bool_p, std::vector<bool> &bool_d, int num_decks){
  int padding = 10;
  int width = SCREEN_WIDTH/52 - 20; // 
  for (int deck=0;deck<num_decks;++deck){
    for (int card=0;card<52;++card){
      ;
    }
  }
}




void DrawButton(Rectangle button, const char* text, Color buttonColor, Color textColor) {
    DrawRectangleRounded(button, 0.25, 10, buttonColor);
    DrawText(text, 
             button.x + button.width / 2 - MeasureText(text, 20) / 2, 
             button.y + button.height / 2 - 10, 
             20, 
             textColor);
}

void DrawCardGrid(int startX, int startY, int cardWidth, int cardHeight, int margin, 
                  std::unordered_set<int>& selectedCards, const std::vector<std::string>& cardValues, 
                  const char* title, int selectionLimit) {
    // Title
    DrawText(title, startX + 10, startY +10, 20, DARKBLUE);

    int cardIndex = 0;

    for (int row = 0; row < CARD_ROWS; ++row) {
        for (int col = 0; col < CARD_COLUMNS; ++col) {
            // Card bounds
            Rectangle card = {
                static_cast<float>(startX + col* (cardWidth + margin)),
                static_cast<float>(startY + row* (cardHeight + margin)) + 50,
                (float)cardWidth,
                (float)cardHeight
            };

            // Highlight if selected
            Color cardColor = selectedCards.count(cardIndex) ? YELLOW : LIGHTGRAY;

            // Draw card
            DrawRectangleRounded(card, 0.1, 10, cardColor);
            DrawText(cardValues[cardIndex % cardValues.size()].c_str(),
                     card.x + card.width / 2 - MeasureText(cardValues[cardIndex % cardValues.size()].c_str(), 20) / 2,
                     card.y + card.height / 2 - 10,
                     20, BLACK);

            // Handle mouse clicks
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), card)) {
                if (selectedCards.count(cardIndex)) {
                    selectedCards.erase(cardIndex);
                } else if (selectedCards.size() < selectionLimit) {
                    selectedCards.insert(cardIndex);
                }
            }

            cardIndex++;
        }
    }
}

std::vector<int> dead_cards_gui(){
  std::vector<int> dead_cards; 
  int margin = 10;
  int cardWidth = (SCREEN_WIDTH / 2 - (CARD_COLUMNS + 1) * margin) / CARD_COLUMNS;
  int cardHeight = (SCREEN_HEIGHT / 2 - (CARD_ROWS + 1) * margin) / CARD_ROWS;

  // UI component dimensions
  int buttonWidth = 200;
  int buttonHeight = 50;
  Rectangle doneButton = {
      static_cast<float>(SCREEN_WIDTH / 2 - buttonWidth / 2),
      SCREEN_HEIGHT - 100,
      (float)buttonWidth,
      (float)buttonHeight
  };
  std::vector<std::string> cardValues = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText("SELECT DEAD CARDS", SCREEN_WIDTH / 2 - MeasureText("SELECT DEAD CARDS", 30) / 2, 20, 30, DARKBLUE);

    // Dealer's card grid
    //DrawCardGrid(margin, 80, cardWidth, cardHeight, margin, dealerSelectedCards, cardValues, "Dealer's Cards", 1);


    //DrawCardGrid(SCREEN_WIDTH / 2 + margin, 80, cardWidth, cardHeight, margin, playerSelectedCards, cardValues, "Player's Cards", 2);


  return dead_cards;
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BLACKJACK");

  SetTargetFPS(60);

  // Card grid dimensions
  int margin = 10;
  int cardWidth = (SCREEN_WIDTH / 2 - (CARD_COLUMNS + 1) * margin) / CARD_COLUMNS;
  int cardHeight = (SCREEN_HEIGHT / 2 - (CARD_ROWS + 1) * margin) / CARD_ROWS;

  // UI component dimensions
  int buttonWidth = 200;
  int buttonHeight = 50;
  Rectangle doneButton = {
      static_cast<float>(SCREEN_WIDTH / 2 - buttonWidth / 2),
      SCREEN_HEIGHT - 100,
      (float)buttonWidth,
      (float)buttonHeight
  };

  // Input box for number of decks
  Rectangle inputBox = {
      static_cast<float>(SCREEN_WIDTH / 2 - buttonWidth / 2),
      SCREEN_HEIGHT - 160,
      (float)buttonWidth,
      40.0f
  };
  std::string numberOfDecks;
  bool inputActive = false;

  // Card selection state
  std::unordered_set<int> dealerSelectedCards;
  std::unordered_set<int> playerSelectedCards;
  std::vector<std::string> cardValues = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

  while (!WindowShouldClose()) {
    // Input handling
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (CheckCollisionPointRec(GetMousePosition(), inputBox)) {
        inputActive = true;
      } 
      else {
        inputActive = false;
      }
    }

    if (inputActive) {
      int key = GetCharPressed();
      while (key > 0) {
        if ((key >= '0' && key <= '9') && numberOfDecks.size() < 5) {
          std::string tmp = numberOfDecks;
          tmp.push_back(char(key));
          int tmp_num = std::stoi(tmp);
          if (tmp_num > 0 && tmp_num <11){
            numberOfDecks.push_back((char)key);
          }
        }
        key = GetCharPressed();
      }

      if (IsKeyPressed(KEY_BACKSPACE) && !numberOfDecks.empty()) {
        numberOfDecks.pop_back();
      }
    }

    // Check if inputs are valid
    bool inputsValid = !numberOfDecks.empty() && dealerSelectedCards.size() == 1 && playerSelectedCards.size() == 2;

    // Handle "Done" button click
    if (inputsValid && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), doneButton)) {
      break; // Close the window if all inputs are valid and button is clicked
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Title
    DrawText("SELECT CARDS FOR DEALER AND PLAYER", SCREEN_WIDTH / 2 - MeasureText("SELECT CARDS FOR DEALER AND PLAYER", 30) / 2, 20, 30, DARKBLUE);

    // Dealer's card grid
    DrawCardGrid(margin, 80, cardWidth, cardHeight, margin, dealerSelectedCards, cardValues, "Dealer's Cards", 1);


    DrawCardGrid(SCREEN_WIDTH / 2 + margin, 80, cardWidth, cardHeight, margin, playerSelectedCards, cardValues, "Player's Cards", 2);

    // Input box
    DrawRectangleRec(inputBox, LIGHTGRAY);
    DrawRectangleLinesEx(inputBox, 2, inputActive ? DARKBLUE : GRAY);

    // Truncate numberOfDecks if too long to fit
    std::string truncatedDecks = numberOfDecks;
    if (MeasureText(numberOfDecks.c_str(), 20) > inputBox.width - 10) {
      while (MeasureText(truncatedDecks.c_str(), 20) > inputBox.width - 10 && !truncatedDecks.empty()) {
        truncatedDecks.pop_back();
      }
      truncatedDecks += "...";
    }

    DrawText(truncatedDecks.c_str(),
             inputBox.x + 5,
             inputBox.y + inputBox.height / 2 - 10,
             20, BLACK);

    DrawText("Number of Decks:", 
             inputBox.x - 200, 
             inputBox.y + inputBox.height / 2 - 10, 
             20, BLACK);

    // "Done" Button
    Color doneButtonColor = inputsValid ? MAROON : GRAY;
    DrawButton(doneButton, "DONE", doneButtonColor, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
