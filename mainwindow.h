#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void pushMenu();
    void timeHit();
private:
    Ui::MainWindow *ui;
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
        HELP
    };
    bool m_is_printed = false;
    QTimer* m_timer;
    QElapsedTimer *m_elapsed;
    int index = 1;
};
#endif // MAINWINDOW_H
