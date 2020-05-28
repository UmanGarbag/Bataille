#ifndef __GAME_H__
# define __GAME_H__

struct boat {
    int x, y;
    int length;
    int horizontal; // boolean: true = horizontal, false = vertical
    int count;
};

struct game {
    struct boat *boat;
    struct game *next;
};

struct game *create_game();
char shoot(struct game *game, int x, int y);

#endif // __GAME_H__
