/********************************************************************************
** Form generated from reading UI file 'dialoglogin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogLogin
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *login;
    QLabel *label_2;
    QLineEdit *senha;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_3;
    QLabel *errorLabel;

    void setupUi(QDialog *DialogLogin)
    {
        if (DialogLogin->objectName().isEmpty())
            DialogLogin->setObjectName(QStringLiteral("DialogLogin"));
        DialogLogin->resize(400, 132);
        gridLayout = new QGridLayout(DialogLogin);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFormAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label = new QLabel(DialogLogin);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        login = new QLineEdit(DialogLogin);
        login->setObjectName(QStringLiteral("login"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy);
        login->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, login);

        label_2 = new QLabel(DialogLogin);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        senha = new QLineEdit(DialogLogin);
        senha->setObjectName(QStringLiteral("senha"));
        sizePolicy.setHeightForWidth(senha->sizePolicy().hasHeightForWidth());
        senha->setSizePolicy(sizePolicy);
        senha->setMinimumSize(QSize(150, 0));
        senha->setStyleSheet(QStringLiteral(""));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, senha);

        pushButton = new QPushButton(DialogLogin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 0));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, pushButton);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        errorLabel = new QLabel(DialogLogin);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));
        errorLabel->setStyleSheet(QStringLiteral("color: red;"));
        errorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(errorLabel);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);


        retranslateUi(DialogLogin);

        QMetaObject::connectSlotsByName(DialogLogin);
    } // setupUi

    void retranslateUi(QDialog *DialogLogin)
    {
        DialogLogin->setWindowTitle(QApplication::translate("DialogLogin", "Login", Q_NULLPTR));
        label->setText(QApplication::translate("DialogLogin", "Login: ", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogLogin", "Senha: ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogLogin", "Login", Q_NULLPTR));
        errorLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogLogin: public Ui_DialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
