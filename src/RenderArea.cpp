#include "RenderArea.hpp"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>

#include <algorithm>

RenderArea::RenderArea(QWidget *parent, QFlags<Qt::WindowType> flags) : QWidget(parent, flags) {
    startTimer(300);
    setFocusPolicy(Qt::StrongFocus);
    blocks.reserve(block_number);
    buildWall();
    genfood();
}

void RenderArea::paintEvent(QPaintEvent *)  {
    QPainter painter(this);


    snake.paintEvent(&painter);
    renderWall(&painter);
    painter.fillRect(food, Qt::red);
}

void RenderArea::renderWall(QPainter* painter) const {
    foreach(const QRect &rect, blocks) {
        painter->fillRect(rect, Qt::darkBlue);
    }
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    using enum Snake::Direction;

    switch (event->key()) {
        case Qt::Key_W:
            if(direction != S) direction = W;
            break;
        case Qt::Key_A:
            if(direction != D) direction = A;
            break;
        case Qt::Key_S:
            if(direction != W) direction = S;
            break;
        case Qt::Key_D:
            if(direction != A) direction = D;
            break;
        default:
            break;
    }
    QWidget::keyPressEvent(event);
}

void RenderArea::timerEvent(QTimerEvent *event) {
    if (isOn){
      snake.move(direction);
      checkFood();
      checkHit();
      repaint();
    }
    QObject::timerEvent(event);
}

void RenderArea::checkHit() {
    const QRect& head = snake.getHead();

    if(snake.selfhit()) {
      qDebug() << "Selfhit";
      isOn = false;
    }

    if(std::any_of(blocks.cbegin(), blocks.cend(), [&](const auto &item) { return item.contains(head); })){
        qDebug() << "blockhit";
        isOn = false;
    }

    if ((head.x() < 0) || (head.y() < 0) || (head.y() > height )|| (head.x() > width)){
        qDebug() << "over";
        isOn = false;
    }


}

void RenderArea::checkFood() {
    if (snake.headContains(food)) {
        genfood();
        snake.eat();
    }
}

void RenderArea::buildWall() {
    while (blocks.size() != block_number){
        int const x = QRandomGenerator::global()->bounded(width / blocksize.width()) * blocksize.width();
        int const y = QRandomGenerator::global()->bounded(height / blocksize.height()) * blocksize.height();

        blocks.insert({{x,y}, blocksize});
    }
}

void RenderArea::genfood() {
    do {
        int const x = QRandomGenerator::global()->bounded(width / blocksize.width()) * blocksize.width();
        int const y = QRandomGenerator::global()->bounded(height / blocksize.height()) * blocksize.height();
        food = {{x,y}, blocksize};
    } while (blocks.contains(food));
}
