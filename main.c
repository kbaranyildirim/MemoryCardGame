#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>

#define GRID_SIZE 4
#define CARD_SIZE 100
#define GAP 20
#define TOP_MARGIN 80
#define SCREEN_WIDTH (GRID_SIZE * CARD_SIZE + (GRID_SIZE + 1) * GAP)
#define SCREEN_HEIGHT (SCREEN_WIDTH + TOP_MARGIN)

int main() {
    if (!al_init()) return -1;
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        al_clear_to_color(al_map_rgb(40, 44, 52));
        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}S