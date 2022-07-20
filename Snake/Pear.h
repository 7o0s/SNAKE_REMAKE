#ifndef PEAR_H
#define PEAR_H
#include "Apple.h"


class Pear: public Apple{
    public:
        Pear();
        void setX(int x){this->x = x;};
        void setY(int y){this->y = y;};
        void check(int dots, int x[Snake::ALL_DOTS], int y[Snake::ALL_DOTS], int pearX, int pearY);
};




#endif // PEAR_H
