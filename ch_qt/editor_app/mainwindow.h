#pragma once

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void onNewDocument();
    void onOpenDocument();
    void onSaveDocument();
    void onSaveAsDocument();
    void onExit();

    void onUndo();
    void onCopy();
    void onCut();
    void onPaste();

    void onZoomIn();
    void onZoomOut();
    void onWordWrap();
    void onFullScreen();

private:
    QString shortFilename(const QString& fileName);
    void updateStatus();
    void updateTitle();
    QTextEdit* m_textEdit { nullptr };
    QString m_fileName;
    QLabel* m_wordWrapLabel { nullptr };
    QLabel* m_zoomLabel { nullptr };
    QAction* m_wordWrapAction { nullptr };
    QAction* m_fullScreenAction { nullptr };
};
