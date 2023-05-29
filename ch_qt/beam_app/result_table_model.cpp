#include "result_table_model.h"

ResultTableModel::ResultTableModel(QObject *parent, BeamAnalysis::BeamModelPtr &beamModel)
    : QAbstractTableModel{parent}, m_beamModel{beamModel}
{
}
