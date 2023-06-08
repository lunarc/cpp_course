#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QJSEngine>
#include <QMainWindow>

#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QValueAxis>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;

    void setData();
    void getData();

    double toDouble(const QString& str, double defValue);

    void update_plot();

private slots:

    void on_plot_button_clicked();
    void on_expression_edit_editingFinished();
    void on_x_min_text_editingFinished();
    void on_x_max_text_editingFinished();
    void on_y_min_text_editingFinished();
    void on_y_max_text_editingFinished();

private:
    Ui::MainWindow* ui;
    QChart* m_chart;
    QChartView* m_chartView;
    QLineSeries* m_series;
    QJSEngine m_jsEngine;
};

#endif // MAINWINDOW_H
