#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlsystem.h"
#include "datasystem.h"
#include "semaphore.h"
#include "train.h"
#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateTrainPosition(int,int,int);
    void updateSemStatus(int,bool);
    void updateLog(int,int,int, int, bool);
    void updateTable(int, int, double);

private:
    void closeEvent (QCloseEvent *event);
    Ui::MainWindow *ui;
    Train *trains[7];
    ControlSystem *controlSys;
    DataSystem *dataSys;
    Semaphore *semaphores[10];
    Semaphore *logSemaphore;
};

#endif // MAINWINDOW_H
