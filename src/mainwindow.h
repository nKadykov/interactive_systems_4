#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "help.h"
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Help;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void pushMenu();
    void timeHit();
    void showHelp();
private:
    Ui::MainWindow *m_ui;
    enum class Menu {
        OPEN = 0,
        SAVE,
        NEW,
        PRINT,
        NETWORK,
        EXIT,
        COPY,
        INSERT,
        DELETE,
        NEW_WINDOW,
        WRAP,
        SAVE_WINDOW,
    };
    bool m_is_printed = false;
    QTimer* m_timer;
    QElapsedTimer *m_elapsed;
    int m_index = 1;
    Help* m_help_dialog;
};
#endif // MAINWINDOW_H
