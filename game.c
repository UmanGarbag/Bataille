#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

#define WIDTH 10
#define HEIGHT 10

#define CARRIER 5
#define BATTLESHIP 4
#define DESTROYER 3
#define SUBMARINE 3
#define PATROL 2

// FIXME add comments!

static struct boat *create_boat(int length) {
    int horizontal = rand() % 2;
    int x = rand() % (WIDTH - (length * horizontal));
    int y = rand() % (HEIGHT - (length * !horizontal));

    struct boat *boat = malloc(sizeof(struct boat));
    if(!boat) {
        return NULL;
    }

    boat->x = x;
    boat->y = y;
    boat->length = length;
    boat->horizontal = horizontal;
    boat->count = 0;

    return boat;
}

static struct game *add_boat(struct game *game, struct boat *boat) {
    struct game *node = malloc(sizeof(struct game));
    if(!node) {
        return NULL;
    }

    node->boat = boat;
    node->next = game;
    return node;
}

static int point_collides(struct game *game, int x, int y, int edit) {
    struct game *tmp = game;
    while(tmp) {
        struct boat *boat = tmp->boat;
        int var = boat->horizontal ? boat->x : boat->y;
        int notvar = boat->horizontal ? boat->y : boat->x;
        for(int i = var; i < var + boat->length; ++i) {
            if(boat->horizontal) {
                if(i == x && boat->y == y) {
                    if(edit) {
                        boat->count++;
                    }
                    return 1;
                }
            } else {
                if(boat->x == x && i == y) {
                    if(edit) {
                        boat->count++;
                    }
                    return 1;
                }
            }
        }
        tmp = tmp->next;
    }
    return 0;
}

static int boat_collides(struct game *game, struct boat *boat) {
    int var = boat->horizontal ? boat->x : boat->y;
    int notvar = boat->horizontal ? boat->y : boat->x;
    for(int i = var; i < var + boat->length; ++i) {
        if(boat->horizontal) {
            if(point_collides(game, i, boat->y, 0)) {
                return 1;
            }
        } else {
            if(point_collides(game, boat->x, i, 0)) {
                return 1;
            }
        }
    }
    return 0;
}

static struct game *add_boat_no_collision(struct game *game, int length) {
    struct boat *boat;
    do {
        boat = create_boat(length);
    } while(boat_collides(game, boat));
    return add_boat(game, boat);
}

struct game *create_game() {
    struct game *game = add_boat_no_collision(NULL, CARRIER);
    game = add_boat_no_collision(game, BATTLESHIP);
    game = add_boat_no_collision(game, DESTROYER);
    game = add_boat_no_collision(game, SUBMARINE);
    game = add_boat_no_collision(game, PATROL);
    return game;
}

static void display_game(struct game *game) {
    char map[WIDTH][HEIGHT];
    for(int i = 0; i < WIDTH; ++i ) {
        for(int j = 0; j < HEIGHT; ++j ) {
            map[i][j] = '.';
        }
    }

    struct game *tmp = game;
    while(tmp) {
        struct boat *boat = tmp->boat;
        int var = boat->horizontal ? boat->x : boat->y;
        for(int i = var; i < var + boat->length; ++i) {
            if(boat->horizontal) {
                map[i][boat->y] = 'B';
            } else {
                map[boat->x][i] = 'B';
            }
        }
        tmp = tmp->next;
    }

    for(int i = 0; i < WIDTH; ++i ) {
        for(int j = 0; j < HEIGHT; ++j ) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int g_map[WIDTH][HEIGHT] = {{}};

char shoot(struct game *game, int x, int y) {
    if(g_map[x][y] == 1) {
        return '\0';
    }
    g_map[x][y] = 1;

    if(point_collides(game, x, y, 1)) {
        struct game *tmp = game;
        while(tmp) {
            struct boat *boat = tmp->boat;
            if(boat->count != -1 && boat->count == boat->length) {
                boat->count = -1;
                return 'C';
            }
            tmp = tmp->next;
        }
        return 'T';
    }

    return 'E';
}

int main() {
    srand(time(NULL));

    struct game *game = create_game();
    display_game(game);

    printf("SHOOT X Y:\n");

    while(1) {
        int x, y;
        scanf("%d %d", &x, &y);

        printf("%c\n", shoot(game, x, y));
    }

    return 0;
}
