#include "slurm_wizard.h"
#include "ui_slurm_wizard.h"

#include <iostream>

SlurmWizardWindow::SlurmWizardWindow(QWidget *parent) : QWidget(parent), ui(std::make_unique< Ui::SlurmWizardWindow >())
{
    ui->setupUi(this);
    updateUi();
}

SlurmWizardWindow::~SlurmWizardWindow()
{
}

void SlurmWizardWindow::updateUi()
{
    ui->scriptEdit->clear();

    auto script = m_job.script();

    ui->scriptEdit->appendPlainText(script.c_str());
}
