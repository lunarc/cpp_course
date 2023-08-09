#include "result_table_model.h"

ResultTableModel::ResultTableModel(QObject *parent, BeamAnalysis::BeamModelPtr &beamModel)
    : QAbstractTableModel{parent}, m_beamModel{beamModel}
{
}

int ResultTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (m_beamModel == nullptr)
        return 0;

    return m_beamModel->beam(0)->evalCount();
}

int ResultTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (m_beamModel == nullptr)
        return 0;

    return 4;
}

QVariant ResultTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (m_beamModel == nullptr)
        return QVariant();

    int row = index.row();
    int column = index.column();
    int evalCount = m_beamModel->beam(0)->evalCount();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (row < 0 || row >= evalCount || column < 0 || column >= 4)
            return QVariant();

        if (column == 0)
        {
            if (m_beamModel->selectedBeam() != nullptr)
                return QString::number(m_beamModel->selectedBeam()->x(row), 'g', 3);
            else
                return 0.0;
        }
        if (column == 1)
        {
            if (m_beamModel->selectedBeam() != nullptr)
                return QString::number(m_beamModel->selectedBeam()->M(row), 'g', 3);
            else
                return 0.0;
        }
        if (column == 2)
        {
            if (m_beamModel->selectedBeam() != nullptr)
                return QString("%1").arg(m_beamModel->selectedBeam()->V(row), 10, 'g', 4);
            // return QString::number(m_beamModel->selectedBeam()->V(row), 'g', 3);
            else
                return 0.0;
        }
        if (column == 3)
        {
            if (m_beamModel->selectedBeam() != nullptr)
                return QString::number(m_beamModel->selectedBeam()->v(row), 'g', 3);
            else
                return 0.0;
        }
    }

    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignRight;
    }

    return QVariant();
}

QVariant ResultTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section < 0 || section >= 4)
            return QVariant();

        if (section == 0)
            return QVariant("x");
        else if (section == 1)
            return QVariant("M");
        else if (section == 2)
            return QVariant("V");
        else if (section == 3)
            return QVariant("y");
        else
            return QVariant();
    }

    return QVariant();
}
