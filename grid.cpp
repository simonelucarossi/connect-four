#include "grid.h"
#include <math.h>

int SCREEN_HEIGHT = 768, SCREEN_WIDTH = 1024;
float PADDING_TOP_BOTTOM = SCREEN_HEIGHT/10;
float PADDING_LEFT_RIGHT = SCREEN_WIDTH/10;

Grid::Grid() {
  this->height = SCREEN_HEIGHT-PADDING_TOP_BOTTOM*2;
  this->width = SCREEN_WIDTH-PADDING_LEFT_RIGHT*2;
  this->cellWidth  = this->width/7;
  this->cellHeight = this->height/6;
  this->cursorPosition = 0;

  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 7; j++) {
      cells[i][j] = 0;
    }
  }
}

/*
 *
 * Public interface
 *
 */

void Grid::moveCursor(direction dir) {
  if(dir == LEFT && this->cursorPosition > 0) {
    this->cursorPosition--;
  } else if(dir == RIGHT && this->cursorPosition < 6) {
    this->cursorPosition++;
  }
}

bool Grid::dropToken(player currentPlayer) {
  for(int i = 5; i >= 0; i--) {
    if(cells[i][this->cursorPosition] == 0) {
      cells[i][this->cursorPosition] = currentPlayer;
      return true;
    }
  }

  return false;
}

/*
 *
 * Draw functions
 *
 */

void Grid::draw() {
  ALLEGRO_COLOR white = al_map_rgb(0,0,0);
  ALLEGRO_COLOR red = al_map_rgb(208,0,0);
  ALLEGRO_COLOR blue = al_map_rgb(30,144,255);

  float coords[7];

  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 7; j++) {
      this->cell(i, j, coords);
      int cellValue = this->cells[i][j];

      al_draw_rectangle(
        coords[0], coords[1],
        coords[2], coords[3],
        white, 5.0
      );

      if(cellValue != 0) {
        if(cellValue == PLAYER1) {
          al_draw_filled_circle(coords[4], coords[5], coords[6], blue);
        } else {
          al_draw_filled_circle(coords[4], coords[5], coords[6], red);
        }
      }
    }
  }

  this->drawCursor();
}

void Grid::drawCursor() {
  ALLEGRO_COLOR white = al_map_rgb(0,0,0);
  float cursorHeight = sqrt(pow(cellWidth/2, 2.0)-pow(cellWidth/4, 2.0));

  float x1 = PADDING_LEFT_RIGHT+(cellWidth/4)+(cellWidth*this->cursorPosition);
  float y1 = PADDING_TOP_BOTTOM/2-(cursorHeight/2);

  float x2 = PADDING_LEFT_RIGHT+(cellWidth/4)*3+(cellWidth*this->cursorPosition);
  float y2 = PADDING_TOP_BOTTOM/2-(cursorHeight/2);

  float x3 = PADDING_LEFT_RIGHT+(cellWidth/4)*2+(cellWidth*this->cursorPosition);
  float y3 = (PADDING_TOP_BOTTOM/2)+(cursorHeight/2);

  al_draw_triangle(x1, y1, x2, y2, x3, y3, white, 5);
}

/*
 *
 * Utility functions
 *
 */

void Grid::cell(int i, int j, float* coords) {
  // x1,y1
  coords[0] = ((this->width/7)*j)+PADDING_LEFT_RIGHT;
  coords[1] = ((this->height/6)*i)+PADDING_TOP_BOTTOM;

  // x2,y2
  coords[2] = ((this->width/7)*j)+cellWidth+PADDING_LEFT_RIGHT;
  coords[3] = ((this->height/6)*i)+cellHeight+PADDING_TOP_BOTTOM;

  // x center, y center
  coords[4] = (coords[0] + coords[2])/2;
  coords[5] = (coords[1] + coords[3])/2;

  // radius
  coords[6] = (cellWidth/100)*25;
}
