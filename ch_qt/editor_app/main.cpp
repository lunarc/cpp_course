#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setAttribute(Qt::AA_DontShowIconsInMenus, true);

    MainWindow window;
    window.show();

    return app.exec();
}
