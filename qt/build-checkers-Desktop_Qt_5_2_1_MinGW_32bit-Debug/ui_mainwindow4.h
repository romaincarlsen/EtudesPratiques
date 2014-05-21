/********************************************************************************
** Form generated from reading UI file 'mainwindow4.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW4_H
#define UI_MAINWINDOW4_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_7;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_14;
    QFrame *border;
    QHBoxLayout *horizontalLayout_8;
    QGridLayout *board_gl;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *size_l;
    QLineEdit *size_tb;
    QHBoxLayout *horizontalLayout_10;
    QLabel *nbLineP1_l;
    QLineEdit *nbLineP1_tb;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *lineEdit_3;
    QComboBox *modeP1_IA;
    QHBoxLayout *horizontalLayout_12;
    QLabel *nbLineP2_l;
    QLineEdit *nbLineP2_tb;
    QHBoxLayout *horizontalLayout_13;
    QLineEdit *lineEdit_4;
    QComboBox *modeP2_IA;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *start;
    QLabel *board_l;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_7 = new QHBoxLayout(centralwidget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 763, 563));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        border = new QFrame(scrollAreaWidgetContents_2);
        border->setObjectName(QStringLiteral("border"));
        border->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(border->sizePolicy().hasHeightForWidth());
        border->setSizePolicy(sizePolicy);
        border->setMinimumSize(QSize(0, 0));
        border->setMaximumSize(QSize(1366, 768));
        border->setSizeIncrement(QSize(1, 1));
        border->setCursor(QCursor(Qt::OpenHandCursor));
        border->setFrameShape(QFrame::NoFrame);
        border->setFrameShadow(QFrame::Plain);
        border->setLineWidth(3);
        border->setMidLineWidth(20);
        horizontalLayout_8 = new QHBoxLayout(border);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        board_gl = new QGridLayout();
        board_gl->setSpacing(0);
        board_gl->setObjectName(QStringLiteral("board_gl"));
        board_gl->setSizeConstraint(QLayout::SetNoConstraint);
        board_gl->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_8->addLayout(board_gl);


        horizontalLayout_14->addWidget(border);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        size_l = new QLabel(scrollAreaWidgetContents_2);
        size_l->setObjectName(QStringLiteral("size_l"));

        horizontalLayout_9->addWidget(size_l);

        size_tb = new QLineEdit(scrollAreaWidgetContents_2);
        size_tb->setObjectName(QStringLiteral("size_tb"));

        horizontalLayout_9->addWidget(size_tb);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        nbLineP1_l = new QLabel(scrollAreaWidgetContents_2);
        nbLineP1_l->setObjectName(QStringLiteral("nbLineP1_l"));

        horizontalLayout_10->addWidget(nbLineP1_l);

        nbLineP1_tb = new QLineEdit(scrollAreaWidgetContents_2);
        nbLineP1_tb->setObjectName(QStringLiteral("nbLineP1_tb"));

        horizontalLayout_10->addWidget(nbLineP1_tb);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        lineEdit_3 = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(160, 20));
        lineEdit_3->setReadOnly(true);

        horizontalLayout_11->addWidget(lineEdit_3);

        modeP1_IA = new QComboBox(scrollAreaWidgetContents_2);
        modeP1_IA->setObjectName(QStringLiteral("modeP1_IA"));

        horizontalLayout_11->addWidget(modeP1_IA);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        nbLineP2_l = new QLabel(scrollAreaWidgetContents_2);
        nbLineP2_l->setObjectName(QStringLiteral("nbLineP2_l"));

        horizontalLayout_12->addWidget(nbLineP2_l);

        nbLineP2_tb = new QLineEdit(scrollAreaWidgetContents_2);
        nbLineP2_tb->setObjectName(QStringLiteral("nbLineP2_tb"));

        horizontalLayout_12->addWidget(nbLineP2_tb);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        lineEdit_4 = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(160, 20));
        lineEdit_4->setReadOnly(true);

        horizontalLayout_13->addWidget(lineEdit_4);

        modeP2_IA = new QComboBox(scrollAreaWidgetContents_2);
        modeP2_IA->setObjectName(QStringLiteral("modeP2_IA"));

        horizontalLayout_13->addWidget(modeP2_IA);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        start = new QPushButton(scrollAreaWidgetContents_2);
        start->setObjectName(QStringLiteral("start"));
        start->setMaximumSize(QSize(75, 23));

        horizontalLayout_2->addWidget(start);


        verticalLayout_2->addLayout(horizontalLayout_2);

        board_l = new QLabel(scrollAreaWidgetContents_2);
        board_l->setObjectName(QStringLiteral("board_l"));
        board_l->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(board_l);


        horizontalLayout_14->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(horizontalLayout_14);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_7->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        size_l->setText(QApplication::translate("MainWindow", "size", 0));
        nbLineP1_l->setText(QApplication::translate("MainWindow", "nb line player 1", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "Mode de jeu du joueur 1", 0));
        nbLineP2_l->setText(QApplication::translate("MainWindow", "nb line player 2", 0));
        lineEdit_4->setText(QApplication::translate("MainWindow", "Mode de jeu du joueur 2", 0));
        start->setText(QApplication::translate("MainWindow", "start", 0));
        board_l->setText(QApplication::translate("MainWindow", "board", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW4_H
