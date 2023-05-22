#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_beamModel = BeamModel::create(3);

    ui->beamView->setBeamModel(m_beamModel);
    this->updateList();
    this->updateControls();
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
    if (ui->beamView->selectedBeam()!=-1)
    {
        auto beam = m_beamModel->beam(ui->beamView->selectedBeam());
        if (beam!=nullptr)
        {
            ui->EEdit->setText(QString::number(beam->E()));
            ui->AEdit->setText(QString::number(beam->A()));
            ui->IyEdit->setText(QString::number(beam->I()));
            ui->qEdit->setText(QString::number(beam->q()));
            ui->lengthEdit->setText(QString::number(beam->l()));
        }

        ui->sectionPropGroup->setTitle("Beam "+QString::number(ui->beamView->selectedBeam()+1)+" ");
    }
    else
    {
        ui->AEdit->setText("");
        ui->EEdit->setText("");
        ui->IyEdit->setText("");
        ui->qEdit->setText("");
        ui->lengthEdit->setText("");
    }
}

void MainWindow::updateList()
{
}

void MainWindow::updateModel()
{
    if (ui->beamView->selectedBeam()!=-1)
    {
        auto beam = m_beamModel->beam(ui->beamView->selectedBeam());
        if (beam!=nullptr)
        {
            beam->l(toDouble(ui->lengthEdit->text(), beam->l()));
            beam->E(toDouble(ui->EEdit->text(), beam->E()));
            beam->A(toDouble(ui->AEdit->text(), beam->A()));
            beam->I(toDouble(ui->IyEdit->text(), beam->I()));
            beam->q(toDouble(ui->qEdit->text(), beam->q()));
        }
    }
}

void MainWindow::on_addSectionAction_triggered()
{
    m_beamModel->add();
    ui->beamView->repaint();
    this->updateControls();
    this->updateList();
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
    this->updateControls();
}


void MainWindow::on_lengthEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->beamView->repaint();
}


void MainWindow::on_EEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->beamView->repaint();
}


void MainWindow::on_AEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->beamView->repaint();
}


void MainWindow::on_IyEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->beamView->repaint();
}


void MainWindow::on_qEdit_textChanged(const QString &arg1)
{
    this->updateModel();
    ui->beamView->repaint();
}

void MainWindow::on_beamView_beamSelected(int idx)
{
    this->updateControls();
}

