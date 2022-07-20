#include <QPainter>
#include <QTime>
#include "Snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:white;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

void Snake::loadImages() {

    dot.load("C:/Studies/OOP/Snake/Dot.png");
    head.load("C:/Studies/OOP/Snake/Head.png");
    apple.load("C:/Studies/OOP/Snake/Apple.png");
    bomb.load("C:/Studies/OOP/Snake/Bomb.png");
    pear.load("C:/Studies/OOP/Snake/Pear.png");

}

void Snake::initGame() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locate();
    locateBomb();


    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);


        for (int z = 0; z < 5; z++) {
            qp.drawImage(bombx[z], bomby[z], bomb);
        }


        qp.drawImage(pear_x, pear_y, pear);



        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {

        gameOver(qp);
    }
}

QString diff, diff0, diff1, diff2;
void Snake::gameOver(QPainter &qp) {
    QString message = "Game over";
    QString count = QString::number(dots);
    QString record = "Итог: " + count + " части" ;
    QString table = "Таблица рекордов:";


    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm. horizontalAdvance(message);
    int textWidth2 = fm. horizontalAdvance(record);
    int textWidth3 = fm. horizontalAdvance(table);

    qp.setPen(QColor(Qt::black));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, -96, "Game over");
    qp.drawText(-textWidth2/2, -80, record);


      if (DELAY == 140){
          diff = " Easy";
      }
      if (DELAY == 100){
          diff = " Norm";
      }
      if (DELAY == 50){
          diff = " Hard";
      }

      int f = 0;

    if (dots > arr[0]){
        arr[2] = arr[1];
        diff2 = diff1;
        arr[1] = arr[0];
        diff1 = diff0;
        arr[0] = dots;
        diff0 = diff;
        f = 0;
    } else
        if (dots > arr[1]){
            arr[2] = arr[1];
            diff2 = diff1;
            arr[1] = dots;
            diff1 = diff;
            f = 1;
        } else
            if (dots > arr[2]){
                arr[2] = dots;
                diff2 = diff;
                f = 2;
            }

    QString count0;
    QString count1;
    QString count2;

    count0 = QString::number(arr[0]);
    count1 = QString::number(arr[1]);
    count2 = QString::number(arr[2]);


    qp.drawText(-textWidth3/2, -48, table);
    qp.drawText(-textWidth3/2, -32, "1) " + count0 + diff0);
    qp.drawText(-textWidth3/2, -16, "2) " + count1 + diff1);
    qp.drawText(-textWidth3/2, 0, "3) " + count2 + diff2);
    qp.drawText(-textWidth3/2, 32, "'1'");
    qp.drawText(-textWidth3/2, 48, "Easy");
    qp.drawText(-textWidth3/2, 68, "'2'");
    qp.drawText(-textWidth3/2, 84, "Normal");
    qp.drawText(-textWidth3/2, 104, "'3'");
    qp.drawText(-textWidth3/2, 120, "Hard");

}


void Snake::checkBomb() {
    for (int z = 0; z < 5; z++) {
        if ((x[0] == bombx[z]) && (y[0] == bomby[z])) {

            dots = 2;
            locateBomb();
            locateApple();
        }
    }
}


void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {

    for (int z = dots; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}


void Snake::locateBomb() {
    for (int z = 0; z < 5; z++) {
        int r = rand() % RAND_POS;
        bombx[z] = (r * DOT_SIZE);

        r = rand() % RAND_POS;
        bomby[z] = (r * DOT_SIZE);
        for (int i = 0; i < dots; i++) {
            if ((bombx[z] == x[i]) && (bomby[z] == y[i])) {
                int r = rand() % RAND_POS;
                bombx[z] = (r * DOT_SIZE);

                r = rand() % RAND_POS;
                bomby[z] = (r * DOT_SIZE);
            }
        }
    }

}


void Snake::timerEvent(QTimerEvent *e, Apple apple, Pear pear) {

    Q_UNUSED(e);

    if (inGame) {

        check();
        checkBomb();
        check();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }


    if ((key == Qt::Key_A) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_D) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_W) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_S) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_1) && (!inGame)){
        leftDirection = false;
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        DELAY = 140;
        inGame = true;
        initGame();
    }

    if ((key == Qt::Key_2) && (!inGame)){
        leftDirection = false;
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        DELAY = 100;
        inGame = true;
        initGame();
    }

    if ((key == Qt::Key_3) && (!inGame)){
        leftDirection = false;
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        DELAY = 50;
        inGame = true;
        initGame();
    }

    if (key == Qt::Key_Escape) {
      if (inGame){
          inGame = false;
          killTimer(timerId);
      }else{
          inGame = true;
          timerId = startTimer(DELAY);
      }
    }

    QWidget::keyPressEvent(e);
}
