#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QStringLiteral>

using namespace Qt::Literals::StringLiterals;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator t;
    if (t.load(QLocale(), "qt"_L1, "_"_L1, "translations"_L1))
        app.installTranslator(&t);

    MainWindow win;
    win.show();

    return app.exec();
}
