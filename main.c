#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
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

int main() {
    if (!al_init()) return -1;
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));

    init_board(); // Arka plan kart kurulumu

    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) running = false;
        al_clear_to_color(al_map_rgb(40, 44, 52));
        al_flip_display();
    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}