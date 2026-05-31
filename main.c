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
#define TOP_MARGIN 80 // Üstteki skor paneli için ayırdığım boşluk
#define SCREEN_WIDTH (GRID_SIZE * CARD_SIZE + (GRID_SIZE + 1) * GAP)
#define SCREEN_HEIGHT (SCREEN_WIDTH + TOP_MARGIN)

typedef struct {
    int id;
    bool isFaceUp;
    bool isMatched;
} Card;

Card board[GRID_SIZE][GRID_SIZE];
ALLEGRO_FONT *font;

int moves = 0;
double start_time;
bool game_won = false;
int final_time = 0;

// --- DOSYA İŞLEMLERİ ---
int get_best_score() {
    FILE *f = fopen("best_score.txt", "r");
    int score = 9999; // Dosya yoksa veya ilk oynayışsa skoru yüksek tut
    if (f) {
        fscanf(f, "%d", &score);
        fclose(f);
    }
    return score;
}

void save_best_score(int score) {
    FILE *f = fopen("best_score.txt", "w");
    if (f) {
        fprintf(f, "%d", score);
        fclose(f);
    }
}

// --- OYUN KURULUMU ---
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

// --- OYUN BİTİŞ KONTROLÜ ---
bool check_win() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (!board[i][j].isMatched) return false;
        }
    }
    return true;
}

// --- EKRAN ÇİZİMİ ---
void draw_board() {
    al_clear_to_color(al_map_rgb(40, 44, 52));

    // Üst Panel: Skor ve Süre
    int current_time = game_won ? final_time : (int)(al_get_time() - start_time);
    int best = get_best_score();

    if (best == 9999) {
        al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Hamle: %d  |  Sure: %d sn", moves, current_time);
    } else {
        al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Hamle: %d  |  Sure: %d sn  |  Rekor: %d", moves, current_time, best);
    }

    if (game_won) {
        al_draw_text(font, al_map_rgb(0, 255, 100), SCREEN_WIDTH / 2, 50, ALLEGRO_ALIGN_CENTER, "TEBRIKLER! OYUN BITTI");
    }

    // Kartların Çizimi (Y koordinatına TOP_MARGIN eklendi)
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

    // Sürenin ekranda saniye saniye akması için 60 FPS'lik bir timer ekledim
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    init_board();
    start_time = al_get_time();
    al_start_timer(timer);

    bool running = true;
    int first_row = -1, first_col = -1;
    int flipped_cards = 0;
    bool redraw = true; // YENİ: Ekranın ne zaman çizileceğini kontrol eden bayrak

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true; // Saniye attığında çizim yapılması gerektiğini işaretle
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !game_won) {
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
                    moves++;
                    draw_board(); // İkinci kartı anında göster

                    if (board[first_row][first_col].id == board[row][col].id) {
                        // Eşleşme Başarılı
                        board[first_row][first_col].isMatched = true;
                        board[row][col].isMatched = true;

                        if (check_win()) {
                            game_won = true;
                            final_time = (int)(al_get_time() - start_time);

                            int best = get_best_score();
                            if (moves < best) save_best_score(moves);
                        }
                    } else {
                        // Eşleşme Başarısız
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


        // Eğer çizim gerekiyorsa VE olay kuyruğu tamamen boşaldıysa çizim yap.

        if (redraw && al_is_event_queue_empty(queue)) {
            draw_board();
            redraw = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}