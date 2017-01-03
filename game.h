#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "enums.h"
#include "grid.cpp"

class Game {
  private:
    // attributes
    bool ended;
    bool quitting;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font;
    Grid grid;
    player currentPlayer;

    // functions
    void initializeAllegro();


  public:
    Game();
    ~Game();

    bool getQuitting();
    void loop();
};
