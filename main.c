#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GRID_SIZE 4
#define CARD_SIZE 100
#define GAP 20
#define TOP_MARGIN 80
#define SCREEN_WIDTH (GRID_SIZE * CARD_SIZE + (GRID_SIZE + 1) * GAP)
#define SCREEN_HEIGHT (SCREEN_WIDTH + TOP_MARGIN)

typedef struct {
    int id;
    bool isFaceUp;
    bool isMatched;
} Card;

Card board[GRID_SIZE][GRID_SIZE];
ALLEGRO_FONT *font;

void init_board() {
    int pairs[GRID_SIZE * GRID_SIZE];
    for (int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) pairs[i] = i / 2;
    srand(time(NULL));
    for (int i = (GRID_SIZE * GRID_SIZE) - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = pairs[i];
        pairs[i] = pairs[j];
        pairs[j] = temp;
    }
    int index = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j].id = pairs[index++];
            board[i][j].isFaceUp = false;
            board[i][j].isMatched = false;
        }
    }
}

void draw_board() {
    al_clear_to_color(al_map_rgb(40, 44, 52));
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            float x = j * (CARD_SIZE + GAP) + GAP;
            float y = i * (CARD_SIZE + GAP) + GAP + TOP_MARGIN;

            if (board[i][j].isMatched || board[i][j].isFaceUp) {
                al_draw_filled_rectangle(x, y, x + CARD_SIZE, y + CARD_SIZE, al_map_rgb(250, 250, 250));
                al_draw_textf(font, al_map_rgb(0, 0, 0), x + CARD_SIZE / 2, y + CARD_SIZE / 2 - 5,
                              ALLEGRO_ALIGN_CENTER, "%d", board[i][j].id);
            } else {
                al_draw_filled_rectangle(x, y, x + CARD_SIZE, y + CARD_SIZE, al_map_rgb(100, 105, 115));
            }
        }
    }
    al_flip_display();
}

int main() {
    if (!al_init()) return -1;
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();

    font = al_create_builtin_font();
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());

    init_board();
    bool running = true;
    int first_row = -1, first_col = -1;
    int flipped_cards = 0;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = event.mouse.x;
            int my = event.mouse.y;
            int col = mx / (CARD_SIZE + GAP);
            int row = (my - TOP_MARGIN) / (CARD_SIZE + GAP);

            if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && !board[row][col].isMatched && !board[row][col].isFaceUp) {
                if (flipped_cards == 0) {
                    board[row][col].isFaceUp = true;
                    first_row = row;
                    first_col = col;
                    flipped_cards = 1;
                } else if (flipped_cards == 1) {
                    board[row][col].isFaceUp = true;
                    draw_board();

                    if (board[first_row][first_col].id == board[row][col].id) {
                        board[first_row][first_col].isMatched = true;
                        board[row][col].isMatched = true;
                    } else {
                        al_rest(0.6);
                        board[first_row][first_col].isFaceUp = false;
                        board[row][col].isFaceUp = false;
                        al_flush_event_queue(queue);
                    }
                    flipped_cards = 0;
                    first_row = -1;
                    first_col = -1;
                }
            }
        }
        if (al_is_event_queue_empty(queue)) {
            draw_board();
        }
    }
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}