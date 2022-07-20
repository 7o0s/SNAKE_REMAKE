#include "Pear.h"
#include <QTime>


Pear::Pear(){
    this->x = 0;
    this->y = 0;
}

void Pear::check(int dots, int x[Snake::ALL_DOTS], int y[Snake::ALL_DOTS], int pearX, int pearY) {

    if ((x[0] == pearX) && (y[0] == pearY)) {

        dots = dots * 2;
        Snake::locateBomb();
        locate();
    }
}
