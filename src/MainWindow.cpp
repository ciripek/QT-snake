#include "MainWindow.hpp"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent, QFlags<Qt::WindowType> flags) : QMainWindow(parent, flags) {
    QPalette pal;
    pal.setColor(QPalette::Window, {255, 255, 230});

    renderArea->setAutoFillBackground(true);
    renderArea->setPalette(pal);
    //renderArea->setFixedSize(750, 750);
    setFixedSize(1000, 750);

    setCentralWidget(renderArea);
}