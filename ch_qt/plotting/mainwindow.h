#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJSEngine>

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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
    Ui::MainWindow *ui;
    QtCharts::QChart* m_chart;
    QtCharts::QChartView* m_chartView;
    QtCharts::QLineSeries* m_series;
    QJSEngine m_jsEngine;

};

#endif // MAINWINDOW_H
