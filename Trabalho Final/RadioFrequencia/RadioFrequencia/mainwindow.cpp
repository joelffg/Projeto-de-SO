#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->started = false;
    this->hide();

    DialogLogin *login = new DialogLogin(this);
    login->setModal(true);
    login->exec();

    while (!started);

    qDebug("rodou");

    ui->comboBox->addItem("Escolher Turma");

    for (map<int, string>::iterator it = turmas.begin(); it != turmas.end(); ++it)
        ui->comboBox->addItem(QString::fromStdString(it->second));

    connect(ui->comboBox,SIGNAL(activated(int)), this,SLOT(clickedClass(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedClass(int index)
{
    map<int, string>::iterator it = turmas.begin();
    for(int i = 0; i++ < index -1 && it != turmas.end(); ++it);

    this->getDiscentesTurma(it->first);

    ui->comboBox->setEnabled(false);

    this->imprimirTurma();


}

void MainWindow::controleFrequencia()
{
    while(true)
    {

    }
}

void MainWindow::getDiscentesTurma(int idTurma) {

    string comando = "python create_list_discente_turma.py " + this->username + " " + this->password + " " + to_string(idTurma) ;
    system(comando.c_str());

    string line = "", file = "", nomeDiscente = "";
    int idDiscente = 0;
    ifstream myfile2 ("nome_id_discente.txt");
    if (myfile2.is_open()) {
        while (getline (myfile2,line)) {
            nomeDiscente = line;
            getline (myfile2,line);
            idDiscente = atoi(line.c_str());
            this->discentes.insert(pair<int,string>(idDiscente,nomeDiscente));
            this->frequencia.insert((pair<int,bool>(idDiscente,false)));
        }
        myfile2.close();
    }
}

void MainWindow::imprimirTurma()
{
    ui->ListaTurma->clear();

    ui->ListaTurma->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    map<int, bool>::iterator it = frequencia.begin();
    for(int i = 0; i < discentes.size(); i++)
    {
        if(it->second)
            ui->ListaTurma->textCursor().insertText("PRESENTE  ");
        else
            ui->ListaTurma->textCursor().insertText("AUSENTE   ");

        ui->ListaTurma->textCursor().insertText(QString::fromStdString(discentes[it->first]));
        ui->ListaTurma->textCursor().insertText("\n");

        ++it;
    }

}
