#include "game.h"
#include "enums.h"

Game::Game() {
  this->ended = false;
  this->quitting = false;
  this->currentPlayer = PLAYER1;
  this->grid = Grid();
  this->initializeAllegro();
}

Game::~Game() {
  al_destroy_display(this->display);
  al_destroy_event_queue(this->event_queue);
}

void Game::initializeAllegro() {
  if(!al_init()) { fprintf(stderr, "failed to initialize allegro!\n"); }

  if(!al_install_keyboard()) { fprintf(stderr, "failed to initialize the keyboard!\n"); }
  if(!al_init_font_addon()) { fprintf(stderr, "failed to initialize fonts!\n"); }
  if(!al_init_ttf_addon()) { fprintf(stderr, "failed to initialize fonts!\n"); }

  this->display = al_create_display(1024, 768);
  this->event_queue = al_create_event_queue();
  this->font = al_load_font("./Minecraft.ttf", 48, 0);

  if(!this->font) { fprintf(stderr, "failed to initialize font!\n"); }
  if(!this->display) { fprintf(stderr, "failed to create display!\n"); }
  if(!this->event_queue) { fprintf(stderr, "failed to create event_queue!\n"); }

  al_register_event_source(this->event_queue, al_get_display_event_source(display));
  al_register_event_source(this->event_queue, al_get_keyboard_event_source());
}

void Game::loop() {
  ALLEGRO_EVENT ev;
  ALLEGRO_TIMEOUT timeout;
  al_init_timeout(&timeout, 0.06);

  if(!this->ended && grid.checkEndGame()) {
    this->ended = true;
  }

  if(!this->ended) {
    if(al_wait_for_event_until(event_queue, &ev, &timeout)) {
      switch(ev.type) {
        case(ALLEGRO_EVENT_DISPLAY_CLOSE):
          this->quitting = true;
          break;
        case(ALLEGRO_EVENT_KEY_CHAR):
          switch(ev.keyboard.keycode) {
            case(ALLEGRO_KEY_ESCAPE):
              this->quitting = true;
              break;
            case(ALLEGRO_KEY_LEFT):
              grid.moveCursor(LEFT);
              break;
            case(ALLEGRO_KEY_RIGHT):
              grid.moveCursor(RIGHT);
              break;
            case(ALLEGRO_KEY_ENTER):
              if(grid.dropToken(this->currentPlayer) && !grid.checkEndGame()) {
                if(this->currentPlayer == PLAYER1) {
                  this->currentPlayer = PLAYER2;
                } else {
                  this->currentPlayer = PLAYER1;
                }
              }
              break;
            default:
              printf("pressed %s \n", al_keycode_to_name(ev.keyboard.keycode));
              break;
          }

          break;
      }
    }

    grid.draw();
  } else {
    grid.draw();
    if(grid.somebodyWon()) {
      if(this->currentPlayer == PLAYER1) {
        al_draw_text(this->font, al_map_rgb(0,0,0), 1024/2, 768-52, ALLEGRO_ALIGN_CENTRE, "Player 1 wins!");
      } else {
        al_draw_text(this->font, al_map_rgb(0,0,0), 1024/2, 768-52, ALLEGRO_ALIGN_CENTRE, "Player 2 wins!");
      }
    } else {
      al_draw_text(this->font, al_map_rgb(0,0,0), 1024/2, 768-52, ALLEGRO_ALIGN_CENTRE, "It's a draw!!");
    }
  }

  al_flip_display();
  al_clear_to_color(al_map_rgb(255, 255, 255));
}


bool Game::getQuitting() {
  return this->quitting;
}
