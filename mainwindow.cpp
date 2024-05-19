#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow),
    m_timer(new QTimer(this)),
    m_elapsed(new QElapsedTimer)
{
    m_help_dialog = new Help;

    m_ui->setupUi(this);

    m_timer->setInterval(1000);
    m_timer->start();
    m_elapsed->start();

    QFont* font = new QFont;
    font->setPointSize(50);

    m_ui->line_edit->setReadOnly(true);
    m_ui->line_edit->setAlignment(Qt::AlignRight);
    m_ui->line_edit->setFont(*font);

    connect(m_timer, &QTimer::timeout, this, &MainWindow::timeHit);

    connect(m_ui->action_open, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_save, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_new_file, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_print, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_network, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_exit, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_copy, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_insert, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_delete, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_new_window, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_wrap, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_save_window, &QAction::triggered, this, &MainWindow::pushMenu);
    connect(m_ui->action_help, &QAction::triggered, this, &MainWindow::showHelp);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::pushMenu() {
    if(m_index > 20) {
        m_index = 1;
    }
    QTableWidgetItem* item1 = new QTableWidgetItem;
    int e = m_elapsed->elapsed();
    item1->setText(QString::number(e / 1000) + "." + QString::number(e % 1000));
    m_ui->table_widget->setItem(m_index, 0, item1);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    int hick = qLn(19) / qLn(2);
    item2->setText(QString::number(hick));
    m_ui->table_widget->setItem(m_index, 1, item2);
    m_is_printed = false;
    m_ui->line_edit->clear();
    m_elapsed->restart();
    m_index++;
}

void MainWindow::timeHit() {
    int time = 3000;
    int elapsed = m_elapsed->elapsed();
    int menu_bar = rand() % 18;
    if(elapsed > time && (!m_is_printed)) {
        switch(menu_bar) {
        case 0:
            m_ui->line_edit->setText(tr("Open"));
            m_is_printed = true;
            break;
        case 2:
            m_ui->line_edit->setText(tr("Save"));
            m_is_printed = true;
            break;
        case 3:
            m_ui->line_edit->setText(tr("New"));
            m_is_printed = true;
            break;
        case 4:
            m_ui->line_edit->setText(tr("Print"));
            m_is_printed = true;
            break;
        case 5:
            m_ui->line_edit->setText(tr("Network"));
            m_is_printed = true;
            break;
        case 6:
            m_ui->line_edit->setText(tr("Exit"));
            m_is_printed = true;
            break;
        case 7:
            m_ui->line_edit->setText(tr("Copy"));
            m_is_printed = true;
            break;
        case 8:
            m_ui->line_edit->setText(tr("Insert"));
            m_is_printed = true;
            break;
        case 9:
            m_ui->line_edit->setText(tr("Delete"));
            m_is_printed = true;
            break;
        case 10:
            m_ui->line_edit->setText(tr("New document"));
            m_is_printed = true;
            break;
        case 11:
            m_ui->line_edit->setText(tr("Save window"));
            m_is_printed = true;
            break;
        case 12:
            m_ui->line_edit->setText(tr("Help"));
            m_is_printed = true;
            break;
        }
    }
}

void MainWindow::showHelp() {
    if(!m_help_dialog) {
        m_help_dialog = new Help;
    }
    m_help_dialog->showHelp();
}
