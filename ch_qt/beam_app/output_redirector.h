#pragma once

#include <iostream>
#include <sstream>

#include <QObject>
#include <QPlainTextEdit>
#include <QTimer>

#include <QDebug>
#include <QPlainTextEdit>
#include <iostream>

// Custom output redirector class
class OutputRedirector : public QObject
{
    Q_OBJECT
public:
    OutputRedirector(QPlainTextEdit* textEdit);
    ~OutputRedirector();

private slots:
    void updateText();

private:
    QPlainTextEdit* textEdit;
    std::streambuf* originalStdout;
    std::stringstream stdoutBuffer;
    QTimer timer;
};
