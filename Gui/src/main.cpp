#include "Parser.h"
#include "Gui.h"

//YOUR PARSER IS THE THING THAT IS FAILING

int main(){
  Gui gui = Gui();
  gui.game_loop();
  Parser parser = Parser("../Data/data.txt");
}
