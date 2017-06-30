/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QPlainTextEdit *ListaTurma;
    QFormLayout *formLayout_2;
    QLabel *labelNumFreq;
    QLabel *NumFreq;
    QGridLayout *gridLayout;
    QPushButton *SendFreqButton;
    QPushButton *CardAddButton;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(533, 393);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);
        comboBox->setMinimumSize(QSize(200, 0));

        verticalLayout_2->addWidget(comboBox);

        ListaTurma = new QPlainTextEdit(centralWidget);
        ListaTurma->setObjectName(QStringLiteral("ListaTurma"));
        ListaTurma->setEnabled(true);
        ListaTurma->setReadOnly(true);

        verticalLayout_2->addWidget(ListaTurma);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        labelNumFreq = new QLabel(centralWidget);
        labelNumFreq->setObjectName(QStringLiteral("labelNumFreq"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelNumFreq);

        NumFreq = new QLabel(centralWidget);
        NumFreq->setObjectName(QStringLiteral("NumFreq"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        NumFreq->setFont(font);
        NumFreq->setStyleSheet(QStringLiteral("color: red;"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, NumFreq);


        verticalLayout_2->addLayout(formLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        SendFreqButton = new QPushButton(centralWidget);
        SendFreqButton->setObjectName(QStringLiteral("SendFreqButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(SendFreqButton->sizePolicy().hasHeightForWidth());
        SendFreqButton->setSizePolicy(sizePolicy3);
        SendFreqButton->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(SendFreqButton, 0, 0, 1, 1, Qt::AlignLeft);

        CardAddButton = new QPushButton(centralWidget);
        CardAddButton->setObjectName(QStringLiteral("CardAddButton"));
        sizePolicy2.setHeightForWidth(CardAddButton->sizePolicy().hasHeightForWidth());
        CardAddButton->setSizePolicy(sizePolicy2);
        CardAddButton->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(CardAddButton, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 533, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RadioFrequ\303\252ncia", Q_NULLPTR));
        labelNumFreq->setText(QApplication::translate("MainWindow", "Alunos Presentes:", Q_NULLPTR));
        NumFreq->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        SendFreqButton->setText(QApplication::translate("MainWindow", "Enviar Frequ\303\252ncia", Q_NULLPTR));
        CardAddButton->setText(QApplication::translate("MainWindow", "Cadastrar Cart\303\243o", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
