#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "enums.h"

class Grid {
  private:
    // attributes
    float height;
    float width;
    float cellWidth;
    float cellHeight;
    int cells[6][7];
    unsigned cursorPosition;
    unsigned filledSpaces;

    // functions
    void drawCursor();
    void cell(int, int, float*);


  public:
    Grid();

    void draw();
    void moveCursor(direction);
    bool dropToken(player);
    bool checkEndGame();
    bool somebodyWon();
};
