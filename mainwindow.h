#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include"playground.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        Playground *ground;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

};
#endif // MAINWINDOW_H
