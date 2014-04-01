/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *ok;
    QLineEdit *input;
    QPushButton *start;
    QLineEdit *size_tb;
    QLineEdit *nbLineP1_tb;
    QLineEdit *nbLineP2_tb;
    QLabel *size_l;
    QLabel *nbLineP1_l;
    QLabel *nbLineP2_l;
    QLabel *board_l;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(703, 424);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ok = new QPushButton(centralWidget);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(610, 270, 75, 23));
        input = new QLineEdit(centralWidget);
        input->setObjectName(QStringLiteral("input"));
        input->setGeometry(QRect(590, 240, 113, 20));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(600, 110, 75, 23));
        size_tb = new QLineEdit(centralWidget);
        size_tb->setObjectName(QStringLiteral("size_tb"));
        size_tb->setGeometry(QRect(580, 10, 113, 20));
        nbLineP1_tb = new QLineEdit(centralWidget);
        nbLineP1_tb->setObjectName(QStringLiteral("nbLineP1_tb"));
        nbLineP1_tb->setGeometry(QRect(575, 40, 113, 20));
        nbLineP2_tb = new QLineEdit(centralWidget);
        nbLineP2_tb->setObjectName(QStringLiteral("nbLineP2_tb"));
        nbLineP2_tb->setGeometry(QRect(580, 70, 113, 20));
        size_l = new QLabel(centralWidget);
        size_l->setObjectName(QStringLiteral("size_l"));
        size_l->setGeometry(QRect(510, 10, 46, 13));
        nbLineP1_l = new QLabel(centralWidget);
        nbLineP1_l->setObjectName(QStringLiteral("nbLineP1_l"));
        nbLineP1_l->setGeometry(QRect(460, 40, 101, 20));
        nbLineP2_l = new QLabel(centralWidget);
        nbLineP2_l->setObjectName(QStringLiteral("nbLineP2_l"));
        nbLineP2_l->setGeometry(QRect(460, 70, 101, 20));
        board_l = new QLabel(centralWidget);
        board_l->setObjectName(QStringLiteral("board_l"));
        board_l->setGeometry(QRect(30, 30, 361, 331));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 703, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        ok->setText(QApplication::translate("MainWindow", "ok", 0));
        start->setText(QApplication::translate("MainWindow", "start", 0));
        size_l->setText(QApplication::translate("MainWindow", "size", 0));
        nbLineP1_l->setText(QApplication::translate("MainWindow", "nb line player 1", 0));
        nbLineP2_l->setText(QApplication::translate("MainWindow", "nb line player 2", 0));
        board_l->setText(QApplication::translate("MainWindow", "board", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
