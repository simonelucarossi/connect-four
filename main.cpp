#include <allegro5/allegro.h>
#include "game.cpp"

int main(int argc, char **argv){
  Game game;

  while(!game.getQuitting()) {
    game.loop();
  }

  return 0;
}
