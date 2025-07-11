#include <QPushButton>
#include <QString>
#include <QIcon>

#include "main_window.h"

using namespace Qt::Literals::StringLiterals;

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      close_button_(new QPushButton(QIcon(":icons/close.svg"_L1), "Close"_L1))
{
    setWindowTitle("Qt-Example"_L1);
    // take ownership
    setCentralWidget(close_button_);
    connect(close_button_, &QPushButton::clicked, this, &MainWindow::close);
    resize(300, 300);
}