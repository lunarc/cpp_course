#ifndef RESULTTABLEMODEL_H
#define RESULTTABLEMODEL_H

#include <QAbstractTableModel>

#include "beam_model.h"

class ResultTableModel : public QAbstractTableModel
{
private:
    BeamAnalysis::BeamModelPtr m_beamModel;

public:
    explicit ResultTableModel(QObject *parent, BeamAnalysis::BeamModelPtr &beamModel);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid())
            return 0;

        if (m_beamModel == nullptr)
            return 0;

        return m_beamModel->beam(0)->evalCount();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid())
            return 0;

        if (m_beamModel == nullptr)
            return 0;

        return 4;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
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
                    return QString::number(m_beamModel->selectedBeam()->V(row), 'g', 3);
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

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
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
};

#endif // RESULTTABLEMODEL_H
