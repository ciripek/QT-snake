#pragma once

#include <QSet>
#include <QWidget>

#include <unordered_set>

#include "Snake.hpp"

class RenderArea final : public QWidget {
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr, QFlags<Qt::WindowType> flags = Qt::WindowFlags());
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    static constexpr qsizetype block_number = 20;
    static constexpr QSize blocksize = {40,40};
    static constexpr int width = 1000;
    static constexpr int height = 750;

    Snake snake{{0, 0}, blocksize};
    Snake::Direction direction = Snake::Direction::S;
    QSet<QRect> blocks;
    QRect food;

    bool isOn = true;

    void buildWall();
    void renderWall(QPainter* painter) const;
    void genfood();
    void checkFood();
    void checkHit();
};


