#pragma once

#include "beam_model.h"

#include <QBrush>
#include <QPen>
#include <QWidget>

class BeamView : public QWidget
{
    Q_OBJECT
  public:
    explicit BeamView(QWidget *parent = nullptr);

    void setBeamModel(BeamModelPtr model);

    int selectedBeam();

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

  signals:
    void beamSelected(int idx);

  private:
    int to_sx(double x);
    int to_sy(double y);

    double to_x(int x);
    double to_y(int x);

    void drawBeams(QPainter &painter);
    void drawSupports(QPainter &painter);
    void drawLoads(QPainter &painter);
    void drawDimensions(QPainter &painter);
    void drawDeflections(QPainter &painter);

    QBrush m_brush;
    QPen m_pen;

    QPen m_selectedBeamPen;
    QPen m_overBeamPen;

    BeamModelPtr m_beamModel;

    double m_margins;
    double m_scaleFactor;
    double m_loadScaleFactor;

    int m_selectedBeam;
    int m_overBeam;
    int m_prevOverBeam;
};
