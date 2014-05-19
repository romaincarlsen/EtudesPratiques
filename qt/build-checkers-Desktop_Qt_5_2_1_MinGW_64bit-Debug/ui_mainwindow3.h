/********************************************************************************
** Form generated from reading UI file 'mainwindow3.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW3_H
#define UI_MAINWINDOW3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *board_l;
    QPushButton *start;
    QLineEdit *size_tb;
    QLabel *nbLineP1_l;
    QGroupBox *modeP1_gr;
    QComboBox *modeP1_IA;
    QLineEdit *nbLineP2_tb;
    QLabel *nbLineP2_l;
    QGroupBox *modeP2_gr;
    QComboBox *modeP2_IA;
    QLineEdit *nbLineP1_tb;
    QLabel *size_l;
    QFrame *border;
    QWidget *gridLayoutWidget_2;
    QGridLayout *board_gl;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        board_l = new QLabel(centralwidget);
        board_l->setObjectName(QStringLiteral("board_l"));
        board_l->setGeometry(QRect(500, 250, 291, 171));
        start = new QPushButton(centralwidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(620, 210, 75, 23));
        size_tb = new QLineEdit(centralwidget);
        size_tb->setObjectName(QStringLiteral("size_tb"));
        size_tb->setGeometry(QRect(600, 10, 81, 20));
        nbLineP1_l = new QLabel(centralwidget);
        nbLineP1_l->setObjectName(QStringLiteral("nbLineP1_l"));
        nbLineP1_l->setGeometry(QRect(510, 40, 81, 20));
        modeP1_gr = new QGroupBox(centralwidget);
        modeP1_gr->setObjectName(QStringLiteral("modeP1_gr"));
        modeP1_gr->setGeometry(QRect(510, 60, 171, 51));
        modeP1_IA = new QComboBox(modeP1_gr);
        modeP1_IA->setObjectName(QStringLiteral("modeP1_IA"));
        modeP1_IA->setGeometry(QRect(30, 20, 121, 22));
        nbLineP2_tb = new QLineEdit(centralwidget);
        nbLineP2_tb->setObjectName(QStringLiteral("nbLineP2_tb"));
        nbLineP2_tb->setGeometry(QRect(600, 120, 81, 20));
        nbLineP2_l = new QLabel(centralwidget);
        nbLineP2_l->setObjectName(QStringLiteral("nbLineP2_l"));
        nbLineP2_l->setGeometry(QRect(510, 120, 81, 20));
        modeP2_gr = new QGroupBox(centralwidget);
        modeP2_gr->setObjectName(QStringLiteral("modeP2_gr"));
        modeP2_gr->setGeometry(QRect(510, 150, 171, 51));
        modeP2_IA = new QComboBox(modeP2_gr);
        modeP2_IA->setObjectName(QStringLiteral("modeP2_IA"));
        modeP2_IA->setGeometry(QRect(20, 20, 121, 22));
        nbLineP1_tb = new QLineEdit(centralwidget);
        nbLineP1_tb->setObjectName(QStringLiteral("nbLineP1_tb"));
        nbLineP1_tb->setGeometry(QRect(600, 40, 81, 20));
        size_l = new QLabel(centralwidget);
        size_l->setObjectName(QStringLiteral("size_l"));
        size_l->setGeometry(QRect(515, 10, 51, 20));
        border = new QFrame(centralwidget);
        border->setObjectName(QStringLiteral("border"));
        border->setEnabled(true);
        border->setGeometry(QRect(30, 20, 451, 391));
        border->setFrameShape(QFrame::NoFrame);
        border->setFrameShadow(QFrame::Plain);
        border->setLineWidth(5);
        border->setMidLineWidth(20);
        gridLayoutWidget_2 = new QWidget(border);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, -10, 451, 391));
        board_gl = new QGridLayout(gridLayoutWidget_2);
        board_gl->setSpacing(0);
        board_gl->setObjectName(QStringLiteral("board_gl"));
        board_gl->setContentsMargins(3, 3, 3, 3);
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Jeu de dames", 0));
        board_l->setText(QApplication::translate("MainWindow", "board", 0));
        start->setText(QApplication::translate("MainWindow", "start", 0));
        nbLineP1_l->setText(QApplication::translate("MainWindow", "nb line player 1", 0));
        modeP1_gr->setTitle(QApplication::translate("MainWindow", "Mode de jeu", 0));
        nbLineP2_l->setText(QApplication::translate("MainWindow", "nb line player 2", 0));
        modeP2_gr->setTitle(QApplication::translate("MainWindow", "Mode de jeu", 0));
        size_l->setText(QApplication::translate("MainWindow", "size", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW3_H
