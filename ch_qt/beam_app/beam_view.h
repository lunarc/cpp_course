#pragma once

#include "beam_model.h"

#include <QBrush>
#include <QPen>
#include <QWidget>

namespace BeamAnalysis
{

class BeamView : public QWidget
{
    Q_OBJECT

private:
    QBrush m_brush;
    QPen m_pen;

    QPen m_selectedBeamPen;
    QPen m_overBeamPen;

    QPen m_momentPen;
    QBrush m_momentBrush;

    QPen m_shearPen;
    QBrush m_shearBrush;

    QPen m_deflectionPen;

    BeamModelPtr m_beamModel;

    double m_margins;
    double m_scaleFactor;
    double m_loadScaleFactor;
    double m_deflectionScaleFactor;
    double m_MscaleFactor;
    double m_VscaleFactor;

    int m_selectedBeam;
    int m_overBeam;
    int m_prevOverBeam;

    bool m_showMoments;
    bool m_showShear;
    bool m_showDeflections;
    bool m_showLoads;

    double to_sx(double x);
    double to_sy(double y);

    double to_x(double x);
    double to_y(double x);

    void drawLineWithArrow(QPainter &painter, int x0, int y0, int x1, int y1);

    void drawBeams(QPainter &painter);
    void drawSupports(QPainter &painter);
    void drawLoads(QPainter &painter);
    void drawDimensions(QPainter &painter);
    void drawDeflections(QPainter &painter);
    void drawM(QPainter &painter);
    void drawV(QPainter &painter);

public:
    explicit BeamView(QWidget *parent = nullptr);

    void setBeamModel(BeamModelPtr model);

    int selectedBeam();

    void showMoments(bool flag);
    void showShear(bool flag);
    void showDeflections(bool flag);
    void showLoads(bool flag);

    bool showLoads();
    bool showShear();
    bool showMoments();
    bool showDeflections();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void beamSelected(int idx);
};

} // namespace BeamAnalysis
