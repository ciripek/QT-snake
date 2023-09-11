#include "Snake.hpp"

#include <QDebug>

#include <algorithm>

Snake::Snake(QPoint top_left, QSize block_size) : head(top_left, block_size) {
    body.push_back({QPoint(top_left.x() - block_size.height(), top_left.y()), block_size});
}

void Snake::paintEvent(QPainter* painter) {
    painter->fillRect(head, Qt::black);

    foreach(const QRect rect, body){
        painter->fillRect(rect, Qt::red);
    }
}

void Snake::move(Snake::Direction dir) {
    for (int i = body.size(); i > 1; i--) {
        body[i - 1] = body[i - 2];
    }

    if (!body.empty()) body[0] = head;

    switch (dir) {
        case Direction::W:
            head.translate(0, -head.height());
            break;
        case Direction::S:
            head.translate(0, +head.height());
            break;
        case Direction::D:
            head.translate(+head.height(), 0);
            break;
        case Direction::A:
            head.translate(-head.height(), 0);
            break;
    }
}

const QRect &Snake::getHead() const {
    return head;
}

void Snake::eat() {
    body.push_back(body.front());
}

bool Snake::selfhit() {
    return std::any_of(body.cbegin(), body.cend(), [this](const auto& bodypart){
        return bodypart.contains(head);
    });
}

bool Snake::headContains(const QRect &rect) const {
  return head.contains(rect);
}
