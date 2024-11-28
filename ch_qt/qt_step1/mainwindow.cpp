#include "mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) :
	QWidget(parent)
{
	// Set the window title
	setWindowTitle("My Text Editor");
	setGeometry(100, 100, 800, 600);

	// Create a new layout
	auto layout = new QHBoxLayout(parent);

	// Create a new label
	auto label = new QLabel("Hello World", parent);
	auto button = new QPushButton("Click me", parent);

	// Add the label to the layout
	layout->addWidget(label);
	layout->addWidget(button);

	this->setLayout(layout);

	// Connect the button click signal to the close slot

	connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
}

void MainWindow::on_button_clicked()
{
	this->close();
}

MainWindow::~MainWindow()
{
}
