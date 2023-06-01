#pragma once

#include <memory>
#include <vector>

#include <QBrush>
#include <QPen>

namespace DrawingKit
{

class DrawableBase
{
  private:
    float m_x;
    float m_y;
    QPen m_pen;
    QBrush m_brush;

  public:
    DrawableBase();

    void setPos(float x, float y);
    void x(float value);
    void y(float value);
    float x();
    float y();

    void setPen(QPen pen);
    void setBrush(QBrush brush);

    void setPenColor(int r, int g, int b, int a = 255);
    void setFillColor(int r, int g, int b, int a = 255);

    void draw(QPainter &painter);

  protected:
    virtual void doDraw(QPainter &painter);
};

typedef std::shared_ptr<DrawableBase> DrawableBasePtr;

class Point : public DrawableBase
{
  public:
    static std::shared_ptr<Point> create();

  protected:
    virtual void doDraw(QPainter &painter) override;
};

typedef std::shared_ptr<Point> PointPtr;

class Ellipse : public DrawableBase
{
  private:
    float m_width;
    float m_height;

  public:
    Ellipse();

    static std::shared_ptr<Ellipse> create();

    void setSize(float width, float height);
    float width();
    float height();
    void width(float value);
    void height(float value);

  protected:
    virtual void doDraw(QPainter &painter) override;
};

class Rectangle : public DrawableBase
{
  private:
    float m_width;
    float m_height;

  public:
    Rectangle();

    static std::shared_ptr<Rectangle> create();

    void setSize(float width, float height);
    float width();
    float height();
    void width(float value);
    void height(float value);

  protected:
    virtual void doDraw(QPainter &painter) override;
};

typedef std::shared_ptr<Ellipse> EllipsePtr;

class Group : public DrawableBase
{
  private:
    std::vector<DrawableBasePtr> m_shapes;

  public:
    static std::shared_ptr<Group> create();

    void add(DrawableBasePtr shape);
    void clear();

  protected:
    virtual void doDraw(QPainter &painter) override;
};

typedef std::shared_ptr<Group> GroupPtr;

}; // namespace DrawingKit
