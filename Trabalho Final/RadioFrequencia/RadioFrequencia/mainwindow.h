#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdio>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool started;
    map<int, string> turmas;
    map<int, string> discentes;
    map<int, bool> frequencia;
    string username, password;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void clickedClass(int);

private:
    Ui::MainWindow *ui;
    void controleFrequencia();
    void getDiscentesTurma(int idTurma);
    void imprimirTurma();
};

#endif // MAINWINDOW_H
