#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    const QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return QApplication::exec();
}
