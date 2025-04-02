#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private:
    QPushButton *close_button_;
};

#endif
