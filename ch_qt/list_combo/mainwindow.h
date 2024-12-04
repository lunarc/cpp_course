#pragma once

#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    void onClearButtonClicked();
    void onItemSelectionChanged();
    void onComboCurrentTextChanged();

private:
    QListWidget *m_listWidget;
    QLineEdit *m_lineEdit;
    QComboBox *m_comboBox;
};
