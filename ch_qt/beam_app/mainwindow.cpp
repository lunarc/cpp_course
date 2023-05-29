#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_resultTableModel{nullptr}
{
    ui->setupUi(this);

    m_beamModel = BeamAnalysis::BeamModel::create(3);
    m_beamModel->connect();
    m_beamModel->solve();

    ui->beamView->setBeamModel(m_beamModel);
    this->updateList();
    this->updateControls();

    m_resultTableModel = new ResultTableModel(this, m_beamModel);

    ui->resultTableView->setModel(m_resultTableModel);

    m_beamModel->setSelectedBeam(0);

    ui->actionShowDeflections->setChecked(ui->beamView->showDeflections());
    ui->actionShowMoments->setChecked(ui->beamView->showMoments());
    ui->actionShowShear->setChecked(ui->beamView->showShear());
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::toDouble(const QString &str, double defValue)
{
    bool ok;
    double value = str.toDouble(&ok);

    if (ok)
        return value;
    else
        return defValue;
}

void MainWindow::updateControls()
{
    if (ui->beamView->selectedBeam() != -1)
    {
        auto beam = m_beamModel->beam(ui->beamView->selectedBeam());
        if (beam != nullptr)
        {
            ui->EEdit->setText(QString::number(beam->E()));
            ui->AEdit->setText(QString::number(beam->A()));
            ui->IyEdit->setText(QString::number(beam->I()));
            ui->qSpin->setValue(beam->q());
            ui->lengthSpin->setValue(beam->l());
        }

        // ui->sectionPropGroup->setTitle("Beam " + QString::number(ui->beamView->selectedBeam() + 1) + " ");
        ui->dockWidget->setWindowTitle("Beam " + QString::number(ui->beamView->selectedBeam() + 1) + " ");
        ui->resultTableView->viewport()->update();
    }
    else
    {
        ui->AEdit->setText("");
        ui->EEdit->setText("");
        ui->IyEdit->setText("");
    }
}

void MainWindow::updateList()
{
}

void MainWindow::updateModel()
{
    if (ui->beamView->selectedBeam() != -1)
    {
        auto beam = m_beamModel->beam(ui->beamView->selectedBeam());
        if (beam != nullptr)
        {
            beam->l(ui->lengthSpin->value());
            beam->E(toDouble(ui->EEdit->text(), beam->E()));
            beam->A(toDouble(ui->AEdit->text(), beam->A()));
            beam->I(toDouble(ui->IyEdit->text(), beam->I()));
            beam->q(ui->qSpin->value());
        }
        m_beamModel->connect();
        m_beamModel->solve();
    }
}

void MainWindow::on_addSectionAction_triggered()
{
    m_beamModel->add();
    ui->beamView->repaint();
    this->updateControls();
    this->updateList();
    ui->resultTableView->viewport()->update();
}

void MainWindow::on_removeSectionAction_triggered()
{
    m_beamModel->removeLast();
    ui->beamView->repaint();
    this->updateControls();
    this->updateList();
}

void MainWindow::on_sectionList_currentRowChanged(int currentRow)
{
    std::cout << currentRow << std::endl;
    ui->resultTableView->viewport()->update();
    this->updateControls();
}

void MainWindow::on_lengthEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_EEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_AEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_IyEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_qEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_beamView_beamSelected(int idx)
{
    m_beamModel->setSelectedBeam(idx);
    ui->resultTableView->viewport()->update();
    this->updateControls();
}

void MainWindow::on_lengthSpin_valueChanged(double arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_qSpin_valueChanged(double arg1)
{
    this->updateModel();
    ui->resultTableView->viewport()->update();
    ui->beamView->repaint();
}

void MainWindow::on_actionShowMoments_triggered(bool checked)
{
    ui->beamView->showMoments(checked);
    ui->beamView->repaint();
}

void MainWindow::on_actionShowShear_triggered(bool checked)
{
    ui->beamView->showShear(checked);
    ui->beamView->repaint();
}

void MainWindow::on_actionShowDeflections_triggered(bool checked)
{
    ui->beamView->showDeflections(checked);
    ui->beamView->repaint();
}
