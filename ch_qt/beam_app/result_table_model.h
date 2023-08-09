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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // RESULTTABLEMODEL_H
