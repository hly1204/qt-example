#include <QApplication>
#include <QMainWindow>
#include <QStringLiteral>

int main(int argc, char *argv[])
{
    using Qt::Literals::StringLiterals::operator""_s;

    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle(u"MainWindow Example"_s);
    window.show();

    return QApplication::exec();
}