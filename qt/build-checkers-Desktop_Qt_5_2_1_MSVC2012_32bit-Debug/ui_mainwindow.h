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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *start;
    QLineEdit *size_tb;
    QLineEdit *nbLineP1_tb;
    QLineEdit *nbLineP2_tb;
    QLabel *size_l;
    QLabel *nbLineP1_l;
    QLabel *nbLineP2_l;
    QLabel *board_l;
    QWidget *gridLayoutWidget;
    QGridLayout *board_gl;
    QGroupBox *modeP1_gr;
    QRadioButton *IA_niv1_P1_r;
    QRadioButton *manualP1_r;
    QRadioButton *IA_niv2_P1_r;
    QGroupBox *modeP2_gr;
    QRadioButton *IA_niv1_P2_r;
    QRadioButton *manual_P2_r;
    QRadioButton *IA_niv2_P2_r;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(797, 523);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(620, 210, 75, 23));
        size_tb = new QLineEdit(centralWidget);
        size_tb->setObjectName(QStringLiteral("size_tb"));
        size_tb->setGeometry(QRect(600, 10, 81, 20));
        nbLineP1_tb = new QLineEdit(centralWidget);
        nbLineP1_tb->setObjectName(QStringLiteral("nbLineP1_tb"));
        nbLineP1_tb->setGeometry(QRect(600, 40, 81, 20));
        nbLineP2_tb = new QLineEdit(centralWidget);
        nbLineP2_tb->setObjectName(QStringLiteral("nbLineP2_tb"));
        nbLineP2_tb->setGeometry(QRect(600, 120, 81, 20));
        size_l = new QLabel(centralWidget);
        size_l->setObjectName(QStringLiteral("size_l"));
        size_l->setGeometry(QRect(515, 10, 51, 20));
        nbLineP1_l = new QLabel(centralWidget);
        nbLineP1_l->setObjectName(QStringLiteral("nbLineP1_l"));
        nbLineP1_l->setGeometry(QRect(510, 40, 81, 20));
        nbLineP2_l = new QLabel(centralWidget);
        nbLineP2_l->setObjectName(QStringLiteral("nbLineP2_l"));
        nbLineP2_l->setGeometry(QRect(510, 120, 81, 20));
        board_l = new QLabel(centralWidget);
        board_l->setObjectName(QStringLiteral("board_l"));
        board_l->setGeometry(QRect(510, 250, 271, 171));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 471, 421));
        board_gl = new QGridLayout(gridLayoutWidget);
        board_gl->setSpacing(0);
        board_gl->setContentsMargins(11, 11, 11, 11);
        board_gl->setObjectName(QStringLiteral("board_gl"));
        board_gl->setContentsMargins(0, 0, 0, 0);
        modeP1_gr = new QGroupBox(centralWidget);
        modeP1_gr->setObjectName(QStringLiteral("modeP1_gr"));
        modeP1_gr->setGeometry(QRect(510, 60, 271, 51));
        IA_niv1_P1_r = new QRadioButton(modeP1_gr);
        IA_niv1_P1_r->setObjectName(QStringLiteral("IA_niv1_P1_r"));
        IA_niv1_P1_r->setGeometry(QRect(100, 20, 82, 17));
        manualP1_r = new QRadioButton(modeP1_gr);
        manualP1_r->setObjectName(QStringLiteral("manualP1_r"));
        manualP1_r->setGeometry(QRect(20, 20, 82, 17));
        manualP1_r->setChecked(true);
        IA_niv2_P1_r = new QRadioButton(modeP1_gr);
        IA_niv2_P1_r->setObjectName(QStringLiteral("IA_niv2_P1_r"));
        IA_niv2_P1_r->setGeometry(QRect(180, 20, 82, 17));
        modeP2_gr = new QGroupBox(centralWidget);
        modeP2_gr->setObjectName(QStringLiteral("modeP2_gr"));
        modeP2_gr->setGeometry(QRect(510, 150, 271, 51));
        IA_niv1_P2_r = new QRadioButton(modeP2_gr);
        IA_niv1_P2_r->setObjectName(QStringLiteral("IA_niv1_P2_r"));
        IA_niv1_P2_r->setGeometry(QRect(100, 20, 82, 17));
        IA_niv1_P2_r->setChecked(true);
        manual_P2_r = new QRadioButton(modeP2_gr);
        manual_P2_r->setObjectName(QStringLiteral("manual_P2_r"));
        manual_P2_r->setGeometry(QRect(20, 20, 82, 17));
        IA_niv2_P2_r = new QRadioButton(modeP2_gr);
        IA_niv2_P2_r->setObjectName(QStringLiteral("IA_niv2_P2_r"));
        IA_niv2_P2_r->setGeometry(QRect(180, 20, 82, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 797, 21));
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
        start->setText(QApplication::translate("MainWindow", "start", 0));
        size_l->setText(QApplication::translate("MainWindow", "size", 0));
        nbLineP1_l->setText(QApplication::translate("MainWindow", "nb line player 1", 0));
        nbLineP2_l->setText(QApplication::translate("MainWindow", "nb line player 2", 0));
        board_l->setText(QApplication::translate("MainWindow", "board", 0));
        modeP1_gr->setTitle(QApplication::translate("MainWindow", "Mode de jeu (\303\240 transformer en liste d\303\251roulante)", 0));
        IA_niv1_P1_r->setText(QApplication::translate("MainWindow", "IA level 1", 0));
        manualP1_r->setText(QApplication::translate("MainWindow", "manual", 0));
        IA_niv2_P1_r->setText(QApplication::translate("MainWindow", "IA level 2", 0));
        modeP2_gr->setTitle(QApplication::translate("MainWindow", "Mode de jeu (\303\240 transformer en liste d\303\251roulante)", 0));
        IA_niv1_P2_r->setText(QApplication::translate("MainWindow", "IA level 1", 0));
        manual_P2_r->setText(QApplication::translate("MainWindow", "manual", 0));
        IA_niv2_P2_r->setText(QApplication::translate("MainWindow", "IA level 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
