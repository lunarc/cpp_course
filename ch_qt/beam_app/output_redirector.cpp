#include "output_redirector.h"

std::vector<std::string> split(const std::string& str, char delim = ' ')
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delim))
    {
        if (!token.empty())
        { // Skip empty tokens
            tokens.push_back(token);
        }
    }
    return tokens;
}

OutputRedirector::OutputRedirector(QPlainTextEdit* textEdit)
    : textEdit(textEdit)
{
    // Redirect stdout
    originalStdout = std::cout.rdbuf();
    std::cout.rdbuf(stdoutBuffer.rdbuf());

    // Connect the buffer to our custom slot
    connect(&timer, &QTimer::timeout, this, &OutputRedirector::updateText);
    timer.start(100); // Check for new text every 100ms
}

OutputRedirector::~OutputRedirector()
{
    // Restore original stdout
    std::cout.rdbuf(originalStdout);
}

void OutputRedirector::updateText()
{
    std::string str = stdoutBuffer.str();

    if (!str.empty())
    {
        auto tokens = split(str, '\n');

        for (const auto& token : tokens)
            textEdit->appendPlainText(QString::fromStdString(token));

        // textEdit->appendPlainText(QString::fromStdString(str));
        stdoutBuffer.str("");
        stdoutBuffer.clear(std::stringstream::goodbit);
    }
}
