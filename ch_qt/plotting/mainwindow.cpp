#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_minX{-6.28},
    m_maxX{6.28},
    m_minY{-1.2},
    m_maxY{1.2}
{
    ui->setupUi(this);

    m_chart = new QtCharts::QChart();

    m_chartView = new QtCharts::QChartView(m_chart);

    ui->centralWidget->layout()->addWidget(m_chartView);

    m_series = new QtCharts::QLineSeries(m_chart);
    m_series->setName("function");
    m_chart->addSeries(m_series);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    this->setData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData()
{
    ui->x_min_text->setText(QString::number(m_minX));
    ui->x_max_text->setText(QString::number(m_maxX));
    ui->y_min_text->setText(QString::number(m_minY));
    ui->y_max_text->setText(QString::number(m_maxY));
}

void MainWindow::getData()
{
    m_minX = toDouble(ui->x_min_text->text(), m_minX);
    m_maxX = toDouble(ui->x_max_text->text(), m_maxX);
    m_minY = toDouble(ui->y_min_text->text(), m_minY);
    m_maxY = toDouble(ui->y_max_text->text(), m_maxY);
    this->setData();
}

double MainWindow::toDouble(const QString &str, double defValue)
{
    bool ok;
    double value = str.toDouble(&ok);
    if (ok)
        return value;
    else
        return defValue;
}

void MainWindow::update_plot()
{
    QString expression = ui->expression_edit->text();
    QString modified_expr = expression;

    this->getData();

    double x = 0.0;
    double y = 0.0;

    m_series->clear();

    x = m_minX;

    while (x<m_maxX)
    {
        // To be able to use math expressions we prefix them with Math.

        QString modified_expr = expression;
        modified_expr.replace("x", QString::number(x));
        modified_expr.replace("sin(", "Math.sin(");
        modified_expr.replace("cos(", "Math.cos(");
        modified_expr.replace("tan(", "Math.tan(");
        modified_expr.replace("sqrt(", "Math.sqrt(");
        modified_expr.replace("abs(", "Math.abs(");
        modified_expr.replace("pow(", "Math.pow(");

        // Evaluate expression using the QJSEngine

        QJSValue value = m_jsEngine.evaluate(modified_expr);
        if (value.isError())
        {
            QMessageBox::warning(this, "Error", "Could not evaluate expression.");
            return;
        }

        double v = value.toNumber();
        m_series->append(x, v);
        x += 0.01;
    }

    // Update chart parameters

    m_series->setName("function of "+expression);
    m_chart->createDefaultAxes();
    m_chart->axes(Qt::Horizontal).first()->setRange(m_minX, m_maxX);
    m_chart->axes(Qt::Vertical).first()->setRange(m_minY, m_maxY);

    m_chartView->update();
}

void MainWindow::on_plot_button_clicked()
{
    this->update_plot();
}

void MainWindow::on_expression_edit_editingFinished()
{
    this->update_plot();
}

void MainWindow::on_x_min_text_editingFinished()
{
    this->update_plot();
}

void MainWindow::on_x_max_text_editingFinished()
{
    this->update_plot();
}

void MainWindow::on_y_min_text_editingFinished()
{
    this->update_plot();
}

void MainWindow::on_y_max_text_editingFinished()
{
    this->update_plot();
}



