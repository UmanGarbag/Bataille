#include <stdio.h>
#include <stdlib.h>
#define WIDTH 10
#define HEIGHT 10
#define length 5

int main(void){
    int horizontal = rand() % 2;
    int x = rand() % (WIDTH - (length * horizontal));
    int y = rand() % (HEIGHT - (length * !horizontal));

    printf("x:%d, y:%d\n",x,y);
    /*
    struct boat boat;
    boat.x = x;
    boat.y = y;
    boat.length = length;
    boat.horizontal = horizontal;
*/


}

