#pragma once

#include <QWidget>
#include <memory>

#include "slurm_task_farm.h"

namespace Ui
{
class SlurmWizardWindow;
}

class SlurmWizardWindow : public QWidget {
    Q_OBJECT

public:
    explicit SlurmWizardWindow(QWidget *parent = 0);
    ~SlurmWizardWindow();

private:
    slurm::Job m_job;

    void updateUi();

private slots:

private:
    std::unique_ptr< Ui::SlurmWizardWindow > ui;
};
