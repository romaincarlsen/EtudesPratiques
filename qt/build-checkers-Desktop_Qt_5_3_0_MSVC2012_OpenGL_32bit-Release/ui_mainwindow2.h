/********************************************************************************
** Form generated from reading UI file 'mainwindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
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
    QHBoxLayout *horizontalLayout_7;
    QFrame *border;
    QHBoxLayout *horizontalLayout;
    QGridLayout *board_gl;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *size_l;
    QLineEdit *size_tb;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nbLineP1_l;
    QLineEdit *nbLineP1_tb;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit;
    QComboBox *modeP1_IA;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nbLineP2_l;
    QLineEdit *nbLineP2_tb;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_2;
    QComboBox *modeP2_IA;
    QPushButton *start;
    QLabel *board_l;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_7 = new QHBoxLayout(centralwidget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        border = new QFrame(centralwidget);
        border->setObjectName(QStringLiteral("border"));
        border->setEnabled(true);
        sizePolicy.setHeightForWidth(border->sizePolicy().hasHeightForWidth());
        border->setSizePolicy(sizePolicy);
        border->setMinimumSize(QSize(0, 0));
        border->setSizeIncrement(QSize(1, 1));
        border->setCursor(QCursor(Qt::OpenHandCursor));
        border->setFrameShape(QFrame::NoFrame);
        border->setFrameShadow(QFrame::Plain);
        border->setLineWidth(3);
        border->setMidLineWidth(20);
        horizontalLayout = new QHBoxLayout(border);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        board_gl = new QGridLayout();
        board_gl->setSpacing(0);
        board_gl->setObjectName(QStringLiteral("board_gl"));
        board_gl->setSizeConstraint(QLayout::SetDefaultConstraint);
        board_gl->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addLayout(board_gl);


        horizontalLayout_7->addWidget(border);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
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

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(160, 20));
        lineEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit);

        modeP1_IA = new QComboBox(centralwidget);
        modeP1_IA->setObjectName(QStringLiteral("modeP1_IA"));

        horizontalLayout_5->addWidget(modeP1_IA);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        nbLineP2_l = new QLabel(centralwidget);
        nbLineP2_l->setObjectName(QStringLiteral("nbLineP2_l"));

        horizontalLayout_2->addWidget(nbLineP2_l);

        nbLineP2_tb = new QLineEdit(centralwidget);
        nbLineP2_tb->setObjectName(QStringLiteral("nbLineP2_tb"));

        horizontalLayout_2->addWidget(nbLineP2_tb);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(160, 20));
        lineEdit_2->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEdit_2);

        modeP2_IA = new QComboBox(centralwidget);
        modeP2_IA->setObjectName(QStringLiteral("modeP2_IA"));

        horizontalLayout_6->addWidget(modeP2_IA);


        verticalLayout->addLayout(horizontalLayout_6);

        start = new QPushButton(centralwidget);
        start->setObjectName(QStringLiteral("start"));
        start->setMaximumSize(QSize(75, 23));

        verticalLayout->addWidget(start);

        board_l = new QLabel(centralwidget);
        board_l->setObjectName(QStringLiteral("board_l"));

        verticalLayout->addWidget(board_l);


        horizontalLayout_7->addLayout(verticalLayout);

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
        size_l->setText(QApplication::translate("MainWindow", "size", 0));
        nbLineP1_l->setText(QApplication::translate("MainWindow", "nb line player 1", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "Mode de jeu du joueur 1", 0));
        nbLineP2_l->setText(QApplication::translate("MainWindow", "nb line player 2", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "Mode de jeu du joueur 2", 0));
        start->setText(QApplication::translate("MainWindow", "start", 0));
        board_l->setText(QApplication::translate("MainWindow", "board", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
