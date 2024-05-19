#include "help.h"

Help::Help(QWidget* parent) : QDialog(parent) {
    m_tool_bar = new QToolBar;
    m_tool_bar->setMinimumSize(500, 50);

    m_buttons[0] = new QToolButton(this);
    m_buttons[0]->setMinimumSize(50, 50);
    m_buttons[0]->setText(tr("Return"));
    connect(m_buttons[0], &QToolButton::triggered, this, &Help::buttonHide);
    m_buttons[1] = new QToolButton(this);
    m_buttons[1]->setMinimumSize(50, 50);
    m_buttons[1]->setText(tr("Back"));
    connect(m_buttons[1], &QToolButton::triggered, this, &Help::buttonBack);
    m_buttons[2] = new QToolButton(this);
    m_buttons[2]->setMinimumSize(50, 50);
    m_buttons[2]->setText(tr("Network"));
    connect(m_buttons[2], &QToolButton::triggered, this, &Help::buttonNetwork);

    m_tool_bar->addWidget(m_buttons[0]);
    m_tool_bar->addWidget(m_buttons[1]);
    m_tool_bar->addWidget(m_buttons[2]);

    m_menu_box = new QGroupBox;
    m_menu_layout = new QGridLayout;
    m_menu_bar = new QMenuBar;

    m_menu_content = new QMenu("&Content");
    m_menu_content->setMaximumSize(10, 10);
    m_menu_pointer = new QMenu("&Pointer");
    m_menu_pointer->setMaximumSize(10, 10);
    m_menu_find = new QMenu("&Find");
    m_menu_find->setMaximumSize(10, 10);

    m_action_content = new QAction;
    m_action_pointer = new QAction;
    m_action_find = new QAction;

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
    m_menu_box->setLayout(m_menu_layout);

    m_text_box = new QGroupBox;
    m_text_browser = new QTextBrowser;
    m_text_browser->setMaximumSize(300, 300);
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
    delete m_tool_bar;
    delete m_menu_box;
    delete m_menu_bar;
    delete m_tree_widget;
    delete m_main_layout;
    for(int i = 0; i <NUMBER; ++i) {
        delete m_buttons[i];
    }
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
    this->close();
}

void Help::actionShowContent() {
    delete m_menu_layout;
    // delete m_menu_bar;
    // delete m_menu_content;
    // delete m_menu_pointer;
    // delete m_menu_find;
    m_menu_box = new QGroupBox;
    m_menu_layout = new QGridLayout;
    m_menu_bar = new QMenuBar;

    m_menu_content = new QMenu("&Content");
    m_menu_content->setMaximumSize(10, 10);
    m_menu_pointer = new QMenu("&Pointer");
    m_menu_pointer->setMaximumSize(10, 10);
    m_menu_find = new QMenu("&Find");
    m_menu_find->setMaximumSize(10, 10);

    m_action_content = new QAction;
    m_action_pointer = new QAction;
    m_action_find = new QAction;

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
    m_menu_box->setLayout(m_menu_layout);

    m_text_box = new QGroupBox;
    m_text_browser = new QTextBrowser;
    m_text_browser->setMaximumSize(300, 300);
    m_text_layout = new QGridLayout;
    m_text_layout->addWidget(m_text_browser);
    m_text_box->setLayout(m_text_layout);
    m_main_layout->addWidget(m_menu_box, 1, 0, 1, 1);

    setLayout(m_main_layout);
}

void Help::actionShowPointer() {
    delete m_menu_layout;

}

void Help::actionShowFind() {
    delete m_menu_layout;

}
