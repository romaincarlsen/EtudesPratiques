/********************************************************************************
** Form generated from reading UI file 'mainwindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *board_gl;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *size_l;
    QLineEdit *size_tb;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nbLineP1_l;
    QLineEdit *nbLineP1_tb;
    QGroupBox *modeP1_gr;
    QComboBox *modeP1_IA;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nbLineP2_l;
    QLineEdit *nbLineP2_tb;
    QGroupBox *modeP2_gr;
    QComboBox *modeP2_IA;
    QPushButton *start;
    QLabel *board_l;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        board_gl = new QGridLayout();
        board_gl->setObjectName(QStringLiteral("board_gl"));

        horizontalLayout->addLayout(board_gl);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        size_l = new QLabel(centralwidget);
        size_l->setObjectName(QStringLiteral("size_l"));

        horizontalLayout_4->addWidget(size_l);

        size_tb = new QLineEdit(centralwidget);
        size_tb->setObjectName(QStringLiteral("size_tb"));

        horizontalLayout_4->addWidget(size_tb);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        nbLineP1_l = new QLabel(centralwidget);
        nbLineP1_l->setObjectName(QStringLiteral("nbLineP1_l"));

        horizontalLayout_3->addWidget(nbLineP1_l);

        nbLineP1_tb = new QLineEdit(centralwidget);
        nbLineP1_tb->setObjectName(QStringLiteral("nbLineP1_tb"));

        horizontalLayout_3->addWidget(nbLineP1_tb);


        verticalLayout->addLayout(horizontalLayout_3);

        modeP1_gr = new QGroupBox(centralwidget);
        modeP1_gr->setObjectName(QStringLiteral("modeP1_gr"));
        modeP1_IA = new QComboBox(modeP1_gr);
        modeP1_IA->setObjectName(QStringLiteral("modeP1_IA"));
        modeP1_IA->setGeometry(QRect(190, 20, 161, 22));

        verticalLayout->addWidget(modeP1_gr);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        nbLineP2_l = new QLabel(centralwidget);
        nbLineP2_l->setObjectName(QStringLiteral("nbLineP2_l"));

        horizontalLayout_2->addWidget(nbLineP2_l);

        nbLineP2_tb = new QLineEdit(centralwidget);
        nbLineP2_tb->setObjectName(QStringLiteral("nbLineP2_tb"));

        horizontalLayout_2->addWidget(nbLineP2_tb);


        verticalLayout->addLayout(horizontalLayout_2);

        modeP2_gr = new QGroupBox(centralwidget);
        modeP2_gr->setObjectName(QStringLiteral("modeP2_gr"));
        modeP2_IA = new QComboBox(modeP2_gr);
        modeP2_IA->setObjectName(QStringLiteral("modeP2_IA"));
        modeP2_IA->setGeometry(QRect(190, 20, 161, 22));

        verticalLayout->addWidget(modeP2_gr);

        start = new QPushButton(centralwidget);
        start->setObjectName(QStringLiteral("start"));
        start->setMaximumSize(QSize(75, 23));

        verticalLayout->addWidget(start);

        board_l = new QLabel(centralwidget);
        board_l->setObjectName(QStringLiteral("board_l"));

        verticalLayout->addWidget(board_l);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        size_l->setText(QApplication::translate("MainWindow", "size", 0));
        nbLineP1_l->setText(QApplication::translate("MainWindow", "nb line player 1", 0));
        modeP1_gr->setTitle(QApplication::translate("MainWindow", "mode de jeu", 0));
        nbLineP2_l->setText(QApplication::translate("MainWindow", "nb line player 2", 0));
        modeP2_gr->setTitle(QApplication::translate("MainWindow", "mode de jeu", 0));
        start->setText(QApplication::translate("MainWindow", "start", 0));
        board_l->setText(QApplication::translate("MainWindow", "board", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
