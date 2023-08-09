#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QJSEngine>
#include <QMainWindow>

#include "beam_model.h"
#include "result_table_model.h"

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

protected:
    void resizeEvent(QResizeEvent *event) override;

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

    void on_actionShowMoments_triggered(bool checked);

    void on_actionShowShear_triggered(bool checked);

    void on_actionShowDeflections_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    BeamAnalysis::BeamModelPtr m_beamModel;
    ResultTableModel *m_resultTableModel;
};

#endif // MAINWINDOW_H
