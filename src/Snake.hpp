#pragma once

#include <QList>
#include <QRect>
#include <QPainter>

class Snake {
public:
    enum class Direction{
        A, S, D, W
    };

    Snake(QPoint top_left, QSize block_size);
    void paintEvent(QPainter* painter);
    void move(Direction dir);

    const QRect &getHead() const;
    void eat();
    bool selfhit();

    bool headContains(const QRect &rect) const;
private:
    QRect head;
    QList<QRect> body;
};
