#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QJSEngine>
#include <QMainWindow>

#include "beam_model.h"
#include "beam_view.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    double toDouble(const QString &str, double defValue);

    void updateControls();
    void updateList();

    void updateModel();

  private slots:
    void on_addSectionAction_triggered();
    void on_removeSectionAction_triggered();
    void on_sectionList_currentRowChanged(int currentRow);

    void on_lengthEdit_textChanged(const QString &arg1);

    void on_EEdit_textChanged(const QString &arg1);

    void on_AEdit_textChanged(const QString &arg1);

    void on_IyEdit_textChanged(const QString &arg1);

    void on_qEdit_textChanged(const QString &arg1);

    void on_beamView_beamSelected(int idx);

    void on_lengthSpin_valueChanged(double arg1);

    void on_qSpin_valueChanged(double arg1);

  private:
    Ui::MainWindow *ui;
    BeamModelPtr m_beamModel;
};

#endif // MAINWINDOW_H
