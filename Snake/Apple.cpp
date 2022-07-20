#include "Apple.h"
#include <QTime>



void Apple::check(int dots, int x[Snake::ALL_DOTS], int y[Snake::ALL_DOTS]) {

    if ((x[0] == *x) && (y[0] == *y)) {

        dots++;
        Snake::locateBomb();
        locate();
    }
}

void Apple::locate() {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());

    Pear pear;

    int a = rand() % 10 + 1;

    if (a != 2){
        int r = rand() % Snake::RAND_POS;
        x = (r * Snake::DOT_SIZE);
        pear.setX(-14);

        r = rand() % Snake::RAND_POS;
        y = (r * Snake::DOT_SIZE);
        pear.setY(-14);

    } else {
            int r = rand() % Snake::RAND_POS;
            pear.setX(r * Snake::DOT_SIZE);
            x = -14;

            r = rand() % Snake::RAND_POS;
            pear.setY(r * Snake::DOT_SIZE);
            y = -14;
        }
}
