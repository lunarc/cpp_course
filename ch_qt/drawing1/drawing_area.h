#pragma once

#include <QBrush>
#include <QPen>
#include <QWidget>

#include "drawing_kit.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
private:
    QBrush m_brush;
    QPen m_pen;
    bool m_firstTime;

    DrawingKit::GroupPtr m_shapes;

public:
    explicit DrawingArea(QWidget* parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    virtual void onSetup();
    virtual void onDraw();
    virtual void onResize();
};
