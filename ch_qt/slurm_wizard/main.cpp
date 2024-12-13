#include "slurm_wizard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SlurmWizardWindow w;
    w.show();

    return a.exec();
}
