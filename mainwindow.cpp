#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ground = new Playground;
    setCentralWidget(ground);

    connect(ground,&Playground::kill,this,&MainWindow::close);
    //connect(ground->snake)
    ground->grabKeyboard();
}

MainWindow::~MainWindow()
{
}

