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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCheckBox *extraAllCheck;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *alt1Radio;
    QRadioButton *alt2Radio;
    QComboBox *comboBox;
    QSlider *horizontalSlider;
    QListWidget *listWidget;
    QLineEdit *valueEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *upperCaseButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(515, 429);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        extraAllCheck = new QCheckBox(centralWidget);
        extraAllCheck->setObjectName(QStringLiteral("extraAllCheck"));
        extraAllCheck->setGeometry(QRect(20, 30, 87, 20));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(210, 10, 134, 82));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        alt1Radio = new QRadioButton(groupBox);
        alt1Radio->setObjectName(QStringLiteral("alt1Radio"));
        alt1Radio->setChecked(true);

        verticalLayout->addWidget(alt1Radio);

        alt2Radio = new QRadioButton(groupBox);
        alt2Radio->setObjectName(QStringLiteral("alt2Radio"));

        verticalLayout->addWidget(alt2Radio);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(210, 120, 111, 26));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 80, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(30, 180, 151, 161));
        valueEdit = new QLineEdit(centralWidget);
        valueEdit->setObjectName(QStringLiteral("valueEdit"));
        valueEdit->setGeometry(QRect(30, 120, 113, 21));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(210, 180, 236, 33));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        upperCaseButton = new QPushButton(widget);
        upperCaseButton->setObjectName(QStringLiteral("upperCaseButton"));

        horizontalLayout->addWidget(upperCaseButton);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        extraAllCheck->setText(QApplication::translate("MainWindow", "CheckBox", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", nullptr));
        alt1Radio->setText(QApplication::translate("MainWindow", "Alternative 1", nullptr));
        alt2Radio->setText(QApplication::translate("MainWindow", "Alternative 2", nullptr));
        upperCaseButton->setText(QApplication::translate("MainWindow", "Uppercase", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
