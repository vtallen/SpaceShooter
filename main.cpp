#include <iostream>
#include "game.h"

int main() {
  //Init srand
  std::srand(static_cast<unsigned>(time(NULL)));

  //Init game engine
  Game game{1200, 800};

  while (game.isRunning()) {
    game.update();
    game.render();
  }

  return 0;
}
