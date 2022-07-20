#ifndef SNAKE_H
#define SNAKE_H


#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {

  public:
      Snake(QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
      QImage dot;
      QImage head;
      QImage apple;
      QImage bomb;
      QImage pear;

      static const int B_WIDTH = 300;
      static const int B_HEIGHT = 300;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 900;
      static const int RAND_POS = 29;
      int DELAY = 140;

      int timerId;
      int dots;
      int apple_x;
      int apple_y;
      int pear_x;
      int pear_y;
      int bomb_x;
      int bomb_y;


      int x[ALL_DOTS];
      int y[ALL_DOTS];
      int arr[3] = {0, 0, 0};
      int bombx[5];
      int bomby[5];


      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame;




      void loadImages();
      void initGame();
      void locateApple();
      void checkApple();
      void locateBomb();
      void checkBomb();
      void checkPear();
      void checkCollision();
      void move();
      void doDrawing();
      void gameOver(QPainter &);

};

#endif // SNAKE_H
