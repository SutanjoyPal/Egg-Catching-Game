/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *workArea;
    QLabel *label;
    QLabel *score;
    QLabel *lives;
    QLabel *label_2;
    QLabel *level;
    QLabel *label_3;
    QLabel *Hens;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1241, 861);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        workArea = new QLabel(centralwidget);
        workArea->setObjectName("workArea");
        workArea->setGeometry(QRect(40, 150, 991, 611));
        workArea->setFrameShape(QFrame::Shape::NoFrame);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(1090, 350, 131, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Algerian")});
        font.setPointSize(24);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 255);"));
        score = new QLabel(centralwidget);
        score->setObjectName("score");
        score->setGeometry(QRect(1090, 400, 131, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("8514oem")});
        font1.setPointSize(15);
        score->setFont(font1);
        score->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 255);"));
        score->setFrameShape(QFrame::Shape::NoFrame);
        lives = new QLabel(centralwidget);
        lives->setObjectName("lives");
        lives->setGeometry(QRect(1090, 590, 131, 31));
        lives->setFont(font1);
        lives->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 0);"));
        lives->setFrameShape(QFrame::Shape::NoFrame);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1090, 530, 111, 51));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(170, 255, 0);"));
        level = new QLabel(centralwidget);
        level->setObjectName("level");
        level->setGeometry(QRect(1090, 200, 131, 31));
        level->setFont(font1);
        level->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        level->setFrameShape(QFrame::Shape::NoFrame);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1090, 140, 131, 61));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 127);"));
        Hens = new QLabel(centralwidget);
        Hens->setObjectName("Hens");
        Hens->setGeometry(QRect(40, 10, 991, 141));
        Hens->setFrameShape(QFrame::Shape::NoFrame);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1241, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        workArea->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Score", nullptr));
        score->setText(QString());
        lives->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Lives", nullptr));
        level->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Level", nullptr));
        Hens->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
