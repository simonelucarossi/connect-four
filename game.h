#include <allegro5/allegro.h>
#include "enums.h"
#include "grid.cpp"

class Game {
  private:
    // attributes
    bool started;
    bool quitting;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
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
