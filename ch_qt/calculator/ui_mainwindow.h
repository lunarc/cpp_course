/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *resultEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *expressionEdit;
    QGridLayout *gridLayout;
    QPushButton *sevenButton;
    QPushButton *eightButton;
    QPushButton *nineButton;
    QPushButton *pushButton_13;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_14;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_15;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *evalButton;
    QPushButton *pushButton_12;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(610, 437);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(label);

        resultEdit = new QLineEdit(centralWidget);
        resultEdit->setObjectName(QStringLiteral("resultEdit"));
        resultEdit->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Grande"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        resultEdit->setFont(font);
        resultEdit->setReadOnly(true);

        horizontalLayout->addWidget(resultEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(label_2);

        expressionEdit = new QLineEdit(centralWidget);
        expressionEdit->setObjectName(QStringLiteral("expressionEdit"));
        expressionEdit->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(expressionEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        sevenButton = new QPushButton(centralWidget);
        sevenButton->setObjectName(QStringLiteral("sevenButton"));

        gridLayout->addWidget(sevenButton, 0, 0, 1, 1);

        eightButton = new QPushButton(centralWidget);
        eightButton->setObjectName(QStringLiteral("eightButton"));

        gridLayout->addWidget(eightButton, 0, 1, 1, 1);

        nineButton = new QPushButton(centralWidget);
        nineButton->setObjectName(QStringLiteral("nineButton"));

        gridLayout->addWidget(nineButton, 0, 2, 1, 1);

        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        gridLayout->addWidget(pushButton_13, 0, 3, 1, 1);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        gridLayout->addWidget(pushButton_14, 1, 3, 1, 1);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_15 = new QPushButton(centralWidget);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));

        gridLayout->addWidget(pushButton_15, 2, 3, 1, 1);

        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 3, 0, 1, 1);

        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout->addWidget(pushButton_11, 3, 1, 1, 1);

        evalButton = new QPushButton(centralWidget);
        evalButton->setObjectName(QStringLiteral("evalButton"));

        gridLayout->addWidget(evalButton, 3, 2, 1, 1);

        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        gridLayout->addWidget(pushButton_12, 3, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(expressionEdit, sevenButton);
        QWidget::setTabOrder(sevenButton, nineButton);
        QWidget::setTabOrder(nineButton, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_5);
        QWidget::setTabOrder(pushButton_5, resultEdit);
        QWidget::setTabOrder(resultEdit, pushButton_7);
        QWidget::setTabOrder(pushButton_7, pushButton_8);
        QWidget::setTabOrder(pushButton_8, pushButton_9);
        QWidget::setTabOrder(pushButton_9, pushButton_10);
        QWidget::setTabOrder(pushButton_10, pushButton_11);
        QWidget::setTabOrder(pushButton_11, pushButton_12);
        QWidget::setTabOrder(pushButton_12, pushButton_13);
        QWidget::setTabOrder(pushButton_13, pushButton_14);
        QWidget::setTabOrder(pushButton_14, pushButton_15);
        QWidget::setTabOrder(pushButton_15, evalButton);
        QWidget::setTabOrder(evalButton, eightButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Result", nullptr));
        resultEdit->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Expression", nullptr));
        sevenButton->setText(QApplication::translate("MainWindow", "7", nullptr));
        eightButton->setText(QApplication::translate("MainWindow", "8", nullptr));
        nineButton->setText(QApplication::translate("MainWindow", "9", nullptr));
        pushButton_13->setText(QApplication::translate("MainWindow", "/", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "4", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindow", "5", nullptr));
        pushButton_6->setText(QApplication::translate("MainWindow", "6", nullptr));
        pushButton_14->setText(QApplication::translate("MainWindow", "*", nullptr));
        pushButton_7->setText(QApplication::translate("MainWindow", "7", nullptr));
        pushButton_8->setText(QApplication::translate("MainWindow", "8", nullptr));
        pushButton_9->setText(QApplication::translate("MainWindow", "9", nullptr));
        pushButton_15->setText(QApplication::translate("MainWindow", "+", nullptr));
        pushButton_10->setText(QApplication::translate("MainWindow", "0", nullptr));
        pushButton_11->setText(QApplication::translate("MainWindow", ",", nullptr));
        evalButton->setText(QApplication::translate("MainWindow", "=", nullptr));
        pushButton_12->setText(QApplication::translate("MainWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
