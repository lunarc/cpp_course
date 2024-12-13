#pragma once

#include <QWidget>
#include <memory>

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
private slots:

private:
    std::unique_ptr< Ui::SlurmWizardWindow > ui;
};
