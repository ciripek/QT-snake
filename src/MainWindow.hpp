#pragma once

#include <QMainWindow>

#include "RenderArea.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr, QFlags<Qt::WindowType> flags = Qt::WindowFlags());
private:
    RenderArea* renderArea = new RenderArea(this);
};

