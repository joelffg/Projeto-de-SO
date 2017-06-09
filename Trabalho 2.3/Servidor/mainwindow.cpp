#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        logSemaphore = new Semaphore(1229, 1);

        for(int i = 0; i < 10; i++)
            semaphores[i] = new Semaphore(1230+i, 1);

        trains[0] = new Train(1,10,130,semaphores);
        trains[1] = new Train(2,150,20,semaphores);
        trains[2] = new Train(3,280,20,semaphores);
        trains[3] = new Train(4,410,130,semaphores);
        trains[4] = new Train(5,280,230,semaphores);
        trains[5] = new Train(6,150,230,semaphores);
        trains[6] = new Train(7,270,130,semaphores);

        controlSys = new ControlSystem(7, trains);
        dataSys = new DataSystem();

        qRegisterMetaType<struct timeval>("struct timeval");

        for(int i = 0; i < 7; i++)
        {
            connect(trains[i],SIGNAL(updatePos(int,int,int)),SLOT(updateTrainPosition(int,int,int)));
            connect(trains[i],SIGNAL(updateSem(int,bool)),SLOT(updateSemStatus(int,bool)));
            connect(trains[i],SIGNAL(updateLog(int,int,int,int,bool)),SLOT(updateLog(int,int,int,int,bool)));
            connect(trains[i],SIGNAL(sendTime(int,struct timeval)),dataSys,SLOT(recvTime(int,struct timeval)));
            trains[i]->start();
        }

        connect(dataSys, SIGNAL(updateData(int,int,double)), SLOT(updateTable(int,int,double)));
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTrainPosition(int id, int x, int y)
{
    switch(id)
    {
        case 1:
            ui->labelTrem01->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem02->setGeometry(x,y,20,20);
            break;
        case 3:
            ui->labelTrem03->setGeometry(x,y,20,20);
            break;
        case 4:
            ui->labelTrem04->setGeometry(x,y,20,20);
            break;
        case 5:
            ui->labelTrem05->setGeometry(x,y,20,20);
            break;
        case 6:
            ui->labelTrem06->setGeometry(x,y,20,20);
            break;
        case 7:
            ui->labelTrem07->setGeometry(x,y,20,20);
            break;
        default:
            break;
    }
}

void MainWindow::updateSemStatus(int id, bool status)
{
    switch(id)
    {
        case 1:
            if (status)
                ui->Sign01->setStyleSheet("color:green");
            else
                ui->Sign01->setStyleSheet("color:red");
            break;
        case 2:
            if (status)
                ui->Sign02->setStyleSheet("color:green");
            else
                ui->Sign02->setStyleSheet("color:red");
            break;
        case 3:
            if (status)
                ui->Sign03->setStyleSheet("color:green");
            else
                ui->Sign03->setStyleSheet("color:red");
            break;
        case 4:
            if (status)
                ui->Sign04->setStyleSheet("color:green");
            else
                ui->Sign04->setStyleSheet("color:red");
            break;
        case 5:
            if (status)
                ui->Sign05->setStyleSheet("color:green");
            else
                ui->Sign05->setStyleSheet("color:red");
            break;
        case 6:
            if (status)
                ui->Sign06->setStyleSheet("color:green");
            else
                ui->Sign06->setStyleSheet("color:red");
            break;
        case 7:
            if (status)
                ui->Sign07->setStyleSheet("color:green");
            else
                ui->Sign07->setStyleSheet("color:red");
            break;
        case 8:
            if (status)
                ui->Sign08->setStyleSheet("color:green");
            else
                ui->Sign08->setStyleSheet("color:red");
            break;
        case 9:
            if (status)
                ui->Sign09->setStyleSheet("color:green");
            else
                ui->Sign09->setStyleSheet("color:red");
            break;
        case 10:
            if (status)
                ui->Sign10->setStyleSheet("color:green");
            else
                ui->Sign10->setStyleSheet("color:red");
            break;
        default:
            break;
    }
}

void MainWindow::updateLog(int trainID, int x, int y, int semID, bool opV)
{
    logSemaphore->P();
    ui->textLog->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    ui->textLog->textCursor().insertText("T0"+QString::number(trainID)+".pos(");

    if(x < 100)
        ui->textLog->textCursor().insertText("0");

    ui->textLog->textCursor().insertText(QString::number(x));
    ui->textLog->textCursor().insertText(",");

    if(y < 100)
        ui->textLog->textCursor().insertText("0");

    ui->textLog->textCursor().insertText(QString::number(y));
    ui->textLog->textCursor().insertText(").Semaphore");

    if(semID < 10)
        ui->textLog->textCursor().insertText("0");

    ui->textLog->textCursor().insertText(QString::number(semID));

    if(opV)
        ui->textLog->textCursor().insertText(".V(");
    else
        ui->textLog->textCursor().insertText(".P(");

    ui->textLog->textCursor().insertText(QString::number(semaphores[semID-1]->getValue()));
    ui->textLog->textCursor().insertText(")\n");

    logSemaphore->V();
}

void MainWindow::updateTable(int id, int field, double value)
{
    QString number = QString("%1").arg(value, 6, 'f',3);
    switch (id) {
        case 1:
            if (field == 0)
                ui->media_1->setText(number);
            else if (field == 1)
                ui->desvP_1->setText(number);
            else
                ui->value_1->setText(number);
            break;
        case 2:
            if (field == 0)
                ui->media_2->setText(number);
            else if (field == 1)
                ui->desvP_2->setText(number);
            else
                ui->value_2->setText(number);
            break;
        case 3:
            if (field == 0)
                ui->media_3->setText(number);
            else if (field == 1)
                ui->desvP_3->setText(number);
            else
                ui->value_3->setText(number);
            break;
        case 4:
            if (field == 0)
                ui->media_4->setText(number);
            else if (field == 1)
                ui->desvP_4->setText(number);
            else
                ui->value_4->setText(number);
            break;
        case 5:
            if (field == 0)
                ui->media_5->setText(number);
            else if (field == 1)
                ui->desvP_5->setText(number);
            else
                ui->value_5->setText(number);
            break;
        case 6:
            if (field == 0)
                ui->media_6->setText(number);
            else if (field == 1)
                ui->desvP_6->setText(number);
            else
                ui->value_6->setText(number);
            break;
        case 7:
            if (field == 0)
                ui->media_7->setText(number);
            else if (field == 1)
                ui->desvP_7->setText(number);
            else
                ui->value_7->setText(number);
            break;
        default:
            break;
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    for(int i = 0; i < 10; i++)
        delete semaphores[i];

    delete logSemaphore;

    delete dataSys;

    event->accept();
}
