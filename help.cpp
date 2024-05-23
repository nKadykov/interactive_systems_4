#include "help.h"
#include <QFile>
#include <QDesktopServices>

Help::Help(QWidget* parent) : QDialog(parent) {
    this->setWindowTitle("Help");

    m_tool_bar = new QToolBar;
    m_tool_bar->setMinimumSize(500, 50);

    m_buttons[0] = new QPushButton(this);
    m_buttons[0]->setMinimumSize(50, 50);
    m_buttons[0]->setText(tr("Return"));
    connect(m_buttons[0], &QPushButton::clicked, this, &Help::buttonHide);
    m_buttons[1] = new QPushButton(this);
    m_buttons[1]->setMinimumSize(50, 50);
    m_buttons[1]->setText(tr("Back"));
    connect(m_buttons[1], &QPushButton::clicked, this, &Help::buttonBack);
    m_buttons[2] = new QPushButton(this);
    m_buttons[2]->setMinimumSize(50, 50);
    m_buttons[2]->setText(tr("Network"));
    connect(m_buttons[2], &QPushButton::clicked, this, &Help::buttonNetwork);

    m_tool_bar->addWidget(m_buttons[0]);
    m_tool_bar->addWidget(m_buttons[1]);
    m_tool_bar->addWidget(m_buttons[2]);

    m_menu_box = new QGroupBox;
    m_menu_layout = new QGridLayout;
    m_menu_bar = new QMenuBar;

    m_menu_content = new QMenu("&Content", m_menu_bar);
    m_menu_content->setMinimumSize(5, 5);
    m_menu_pointer = new QMenu("&Pointer");
    m_menu_pointer->setMinimumSize(5, 5);
    m_menu_find = new QMenu("&Find");
    m_menu_find->setMinimumSize(5, 5);

    m_action_content = new QAction(tr("Content"));
    m_action_pointer = new QAction(tr("Pointer"));
    m_action_find = new QAction(tr("Find"));

    m_menu_content->addAction(m_action_content);
    m_menu_pointer->addAction(m_action_pointer);
    m_menu_find->addAction(m_action_find);

    m_menu_bar->addMenu(m_menu_content);
    m_menu_bar->addMenu(m_menu_pointer);
    m_menu_bar->addMenu(m_menu_find);

    connect(m_action_content, &QAction::triggered, this, &Help::actionShowContent);
    connect(m_action_pointer, &QAction::triggered, this, &Help::actionShowPointer);
    connect(m_action_find, &QAction::triggered, this, &Help::actionShowFind);

    m_menu_layout->addWidget(m_menu_bar);

    m_tree_widget = new QTreeWidget;
    QTreeWidgetItem* tree_item_1 = new QTreeWidgetItem;
    tree_item_1->setText(0, "Лабораторные работы");
    for(int i = 0; i < 4; ++i) {
        m_tree_child[i] = new QTreeWidgetItem();
        m_tree_child[i]->setText(0, QString::number(i+1));
        tree_item_1->addChild(m_tree_child[i]);
        m_tree_child_child[i] = new QTreeWidgetItem;
        m_tree_child_child_2[i] = new QTreeWidgetItem;
        m_tree_child_child[i]->setText(0, "Цель " + QString::number(i + 1));
        m_tree_child[i]->addChild(m_tree_child_child[i]);
        m_tree_child_child_2[i]->setText(0, "Задачи " + QString::number(i + 1));
        m_tree_child[i]->addChild(m_tree_child_child_2[i]);
    }
    m_tree_widget->addTopLevelItem(tree_item_1);

    m_menu_layout->addWidget(m_tree_widget);
    m_menu_box->setLayout(m_menu_layout);

    m_text_box = new QGroupBox;
    m_text_browser = new QTextBrowser(this);
    m_text_browser->setMinimumSize(500, 500);
    m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/begin_page.html"));

    QFile file("e:/Qt Projects/interactive_systems_4/html/begin_page.html");
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("file not found");
    }
    m_text_browser->setHtml(file.readAll());

    connect(m_tree_widget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
                     this, SLOT(setPage(QTreeWidgetItem*, int)));



    m_text_layout = new QGridLayout;
    m_text_layout->addWidget(m_text_browser);
    m_text_box->setLayout(m_text_layout);

    m_main_layout = new QGridLayout;
    m_main_layout->addWidget(m_tool_bar, 0, 0, 1, 2);
    m_main_layout->addWidget(m_menu_box, 1, 0, 1, 1);
    m_main_layout->addWidget(m_text_box, 1, 1, 1, 1);

    setLayout(m_main_layout);
}

Help::~Help() {
}

void Help::showHelp() {
    this->show();
}

void Help::buttonHide() {
    this->hide();
}

void Help::buttonBack() {
    this->hide();
}

void Help::buttonNetwork() {
    QString link = "file:E:/Qt Projects/interactive_systems_4/html/begin_page.html";
    QDesktopServices::openUrl(QUrl(link));
}

void Help::actionShowContent() {
    m_menu_layout->addWidget(m_menu_bar);
    m_menu_box->setLayout(m_menu_layout);
    m_main_layout->addWidget(m_menu_box, 1, 0, 1, 1);
}

void Help::actionShowPointer() {
    if(m_menu_box) {
        delete m_menu_box;
        m_menu_box = nullptr;
    }
    m_menu_box = new QGroupBox;
}

void Help::actionShowFind() {
    if(m_menu_box) {
        delete m_menu_box;
        m_menu_box = nullptr;
    }
}

void Help::setPage(QTreeWidgetItem* item, int i) {
    if(item->text(0).contains("Цель 1")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_1_purpose.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_1_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Цель 2")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_2_purpose.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_2_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Цель 3")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_3_purpose.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_3_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Цель 4")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_4_purpose.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_4_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }

    if(item->text(0).contains("Задачи 1")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_1_2.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_1_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Задачи 2")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_2_2.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_2_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Задачи 3")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_3_2.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_3_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Задачи 4")) {
        m_text_browser->setSource(QUrl("e:/Qt Projects/interactive_systems_4/html/lab_4_2.html"));
        QFile file("e:/Qt Projects/interactive_systems_4/html/lab_4_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }

}

