#include "slurm_wizard.h"
#include "ui_slurm_wizard.h"

SlurmWizardWindow::SlurmWizardWindow(QWidget *parent) : QWidget(parent), ui(std::make_unique< Ui::SlurmWizardWindow >())
{
    ui->setupUi(this);
}

SlurmWizardWindow::~SlurmWizardWindow()
{
}
