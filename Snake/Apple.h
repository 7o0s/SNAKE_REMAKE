#ifndef APPLE_H
#define APPLE_H
#include "Snake.h"


class Apple{

    public:
        void locate();
        virtual void check(int dots, int x[Snake::ALL_DOTS], int y[Snake::ALL_DOTS]);

        int x;
        int y;

};

#endif // APPLE_H
