#include <QApplication>
#include <QPushButton>
#include "Window.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication app (argc, argv);
    QWidget *window = new Window;
    window->show();
    return app.exec();
}
