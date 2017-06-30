#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(MainWindow* mwp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    this->mw = mwp;
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_pushButton_clicked()
{
    if(ui->login->text() != ui->senha->text())
        ui->errorLabel->setText("Senha Incorreta!");
    else
    {
        map<int, string> turmas = this->getTurmasDocente(ui->login->text().toStdString(), ui->senha->text().toStdString());

        if(turmas.size() == 0)
            ui->errorLabel->setText("Não possui Turmas Ativas!");
        else
        {
            mw->started = true;
            mw->turmas = turmas;
            mw->username = ui->login->text().toStdString();
            mw->password = ui->senha->text().toStdString();
            mw->show();
            mw->activateWindow();
            mw->setFocus();
            this->hide();
        }
    }

}

map<int, string> DialogLogin::getTurmasDocente(string username, string password) {

    // Usa a API do sigaa
    string comando = "python get_turma.py " + username + " " + password;
    system(comando.c_str());

    string line = "", file = "", nomeTurma = "";
    int idTurma = 0;
    map<int,string> turmas;
    ifstream myfile2 ("turmas_docente.txt");
    if (myfile2.is_open()) {
        while (getline (myfile2,line)) {
            nomeTurma = line;
            getline (myfile2,line);
            idTurma = atoi(line.c_str());
            turmas.insert(pair<int,string>(idTurma,nomeTurma));
        }
        myfile2.close();
    }
    return turmas;
}
