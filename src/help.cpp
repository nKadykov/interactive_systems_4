#include "help.h"
#include <QFile>
#include <QDesktopServices>
#include <QMessageBox>
#include <QDir>
#include <QListWidgetItem>

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

    QFile file("html/begin_page.html");
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("file not found");
    }
    m_text_browser->setHtml(file.readAll());

    connect(m_tree_widget, &QTreeWidget::itemClicked, this, &Help::setPage);

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
    delete m_text_box;
    delete m_menu_content;
    delete m_menu_pointer;
    delete m_menu_find;
    delete m_menu_bar;
    if(m_tree_widget)
        delete m_tree_widget;
    delete m_main_layout;
    delete m_menu_layout;
    delete m_text_layout;
    enum {NUMBER = 3};
    QPushButton* m_buttons[NUMBER];
    for(int i = 0; i < NUMBER; ++i) {
        delete m_buttons[i];
    }
    delete m_text_browser;
    delete m_action_content;
    delete m_action_pointer;
    delete m_action_find;
    enum {CHILDS = 4};
    for(int i = 0; i < CHILDS; ++i ) {
        delete m_tree_child[i];
        delete m_tree_child_child[i];
        delete m_tree_child_child_2[i];
    }
    if(m_search_label != nullptr)
        delete m_search_label;
    if(m_search_button != nullptr)
        delete m_search_button;
    if(m_search_edit != nullptr)
        delete m_search_edit;
    if(m_file_list != nullptr)
        delete m_file_list;
    if(m_tree_pointer != nullptr)
        delete m_tree_pointer;
    for(int i = 0; i < POINTERS; ++i)
        delete m_tree_child_pointer[POINTERS];
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
    QString link = "file:html/begin_page.html";
    QDesktopServices::openUrl(QUrl(link));
}

void Help::actionShowContent() {
    if(m_search_label != nullptr) {
        delete m_search_label;
        m_search_label = nullptr;
    }
    if(m_search_edit != nullptr) {
        delete m_search_edit;
        m_search_edit = nullptr;
    }
    if(m_search_button != nullptr) {
        delete m_search_label;
        m_search_label = nullptr;
    }
    if(m_file_list != nullptr) {
        delete m_file_list;
        m_file_list = nullptr;
    }

    if(m_tree_pointer != nullptr) {
        delete m_tree_pointer;
        m_tree_pointer = nullptr;
    }

    if(m_tree_widget == nullptr) {
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
        connect(m_tree_widget, &QTreeWidget::itemClicked, this, &Help::setPage);
    }
}

void Help::actionShowPointer() {

    if(m_tree_widget) {
        delete m_tree_widget;
        m_tree_widget = nullptr;
    }

    if(m_search_label != nullptr) {
        delete m_search_label;
        m_search_label = nullptr;
    }
    if(m_search_edit != nullptr) {
        delete m_search_edit;
        m_search_edit = nullptr;
    }
    if(m_search_button != nullptr) {
        delete m_search_label;
        m_search_label = nullptr;
    }
    if(m_file_list != nullptr) {
        delete m_file_list;
        m_file_list = nullptr;
    }

    if(m_tree_pointer == nullptr) {
        m_tree_pointer = new QTreeWidget;
        for(int i = 0; i < 8; ++i) {
            m_tree_child_pointer[i] = new QTreeWidgetItem();
            if(i % 2 == 0)
                m_tree_child_pointer[i]->setText(0, "Цель " + QString::number(i / 2 + 1));
            if(i % 2 != 0)
                m_tree_child_pointer[i]->setText(0, "Задачи " + QString::number(i / 2 + 1));
            m_tree_pointer->addTopLevelItem(m_tree_child_pointer[i]);
        }
        m_menu_layout->addWidget(m_tree_pointer);
        connect(m_tree_pointer, &QTreeWidget::itemClicked, this, &Help::setPage);
    }
}

void Help::actionShowFind() {
    if(m_tree_widget) {
        delete m_tree_widget;
        m_tree_widget = nullptr;
    }

    if(m_tree_pointer != nullptr) {
        delete m_tree_pointer;
        m_tree_pointer = nullptr;
    }

    if(m_search_label == nullptr)
        m_search_label = new QLabel("Search text: ", this);
    if(m_search_edit == nullptr)
        m_search_edit = new QLineEdit(this);
    if(m_search_button == nullptr)
        m_search_button = new QPushButton("Search", this);
    if(m_file_list == nullptr)
        m_file_list = new QListWidget(this);

    m_menu_layout->addWidget(m_search_label);
    m_menu_layout->addWidget(m_search_edit);
    m_menu_layout->addWidget(m_search_button);
    m_menu_layout->addWidget(m_file_list);

    connect(m_search_button, &QPushButton::clicked, this, &Help::performSearch);
    connect(m_file_list, &QListWidget::itemClicked, this, &Help::onLinkClicked);
}

void Help::setPage(QTreeWidgetItem* item, int i) {
    if(item->text(0).contains("Цель 1")) {
        QFile file("html/lab_1_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Цель 2")) {
        QFile file("html/lab_2_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Цель 3")) {
        QFile file("html/lab_3_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Цель 4")) {
        QFile file("html/lab_4_purpose.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }

    if(item->text(0).contains("Задачи 1")) {
        QFile file("html/lab_1_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Задачи 2")) {
        QFile file("html/lab_2_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Задачи 3")) {
        QFile file("html/lab_3_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
    if(item->text(0).contains("Задачи 4")) {
        QFile file("html/lab_4_2.html");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("file not found");
        }
        m_text_browser->setHtml(file.readAll());
    }
}

void Help::performSearch() {
    QString directory_path = "html";
    m_search_text = m_search_edit->text();

    if(m_search_text.isEmpty()) {
        return;
    }

    m_file_list->clear();

    QDir directory(directory_path);

    QStringList filters;
    filters << "*.html";
    QFileInfoList files = directory.entryInfoList(filters, QDir::Files);

    m_file_list->clear();

    foreach(const QFileInfo &fileinfo, files) {
        QFile file(fileinfo.filePath());
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString file_content = in.readAll();
            if(file_content.contains(m_search_text, Qt::CaseInsensitive)) {
                QListWidgetItem* item = new QListWidgetItem(fileinfo.fileName(), m_file_list);
                item->setData(Qt::UserRole, fileinfo.filePath());
            }
        }
    }
}

void Help::onLinkClicked(QListWidgetItem* item) {
    QString file_path = item->data(Qt::UserRole).toString();
    QString search_text = m_search_text;

    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File error", "Unable to open file");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();

    m_text_browser->toPlainText();
    m_text_browser->setHtml(content);
    m_text_browser->append(search_text);

    QTextCursor cursor(m_text_browser->document());
    QTextCharFormat format;
    format.setBackground(Qt::yellow);

    cursor.beginEditBlock();

    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = m_text_browser->document()->find(search_text, cursor);
        if (!cursor.isNull()) {
            cursor.mergeCharFormat(format);
        }
    }

    cursor.endEditBlock();
}

// #include "help.h"
// #include <QFile>
// #include <QDesktopServices>
// #include <QMessageBox>
// #include <QDir>

// Help::Help(QWidget* parent) : QDialog(parent) {
//     this->setWindowTitle("Help");

//     m_tool_bar = new QToolBar;
//     m_tool_bar->setMinimumSize(500, 50);

//     m_buttons[0] = new QPushButton(this);
//     m_buttons[0]->setMinimumSize(50, 50);
//     m_buttons[0]->setText(tr("Return"));
//     connect(m_buttons[0], &QPushButton::clicked, this, &Help::buttonHide);
//     m_buttons[1] = new QPushButton(this);
//     m_buttons[1]->setMinimumSize(50, 50);
//     m_buttons[1]->setText(tr("Back"));
//     connect(m_buttons[1], &QPushButton::clicked, this, &Help::buttonBack);
//     m_buttons[2] = new QPushButton(this);
//     m_buttons[2]->setMinimumSize(50, 50);
//     m_buttons[2]->setText(tr("Network"));
//     connect(m_buttons[2], &QPushButton::clicked, this, &Help::buttonNetwork);

//     m_tool_bar->addWidget(m_buttons[0]);
//     m_tool_bar->addWidget(m_buttons[1]);
//     m_tool_bar->addWidget(m_buttons[2]);

//     m_menu_box = new QGroupBox;
//     m_menu_layout = new QGridLayout;
//     m_menu_bar = new QMenuBar;

//     m_menu_content = new QMenu("&Content", m_menu_bar);
//     m_menu_content->setMinimumSize(5, 5);

//     m_menu_pointer = new QMenu("&Pointer");
//     m_menu_pointer->setMinimumSize(5, 5);

//     m_menu_find = new QMenu("&Find");
//     m_menu_find->setMinimumSize(5, 5);

//     m_action_content = new QAction(tr("Content"));
//     m_action_pointer = new QAction(tr("Pointer"));
//     m_action_find = new QAction(tr("Find"));

//     m_menu_content->addAction(m_action_content);
//     m_menu_pointer->addAction(m_action_pointer);
//     m_menu_find->addAction(m_action_find);

//     m_menu_bar->addMenu(m_menu_content);
//     m_menu_bar->addMenu(m_menu_pointer);
//     m_menu_bar->addMenu(m_menu_find);

//     connect(m_action_content, &QAction::triggered, this, &Help::actionShowContent);
//     connect(m_action_pointer, &QAction::triggered, this, &Help::actionShowPointer);
//     connect(m_action_find, &QAction::triggered, this, &Help::actionShowFind);

//     m_menu_layout->addWidget(m_menu_bar);

//     m_tree_widget = new QTreeWidget;
//     QTreeWidgetItem* tree_item_1 = new QTreeWidgetItem;
//     tree_item_1->setText(0, "Лабораторные работы");
//     for(int i = 0; i < 4; ++i) {
//         m_tree_child[i] = new QTreeWidgetItem();
//         m_tree_child[i]->setText(0, QString::number(i+1));
//         tree_item_1->addChild(m_tree_child[i]);
//         m_tree_child_child[i] = new QTreeWidgetItem;
//         m_tree_child_child_2[i] = new QTreeWidgetItem;
//         m_tree_child_child[i]->setText(0, "Цель " + QString::number(i + 1));
//         m_tree_child[i]->addChild(m_tree_child_child[i]);
//         m_tree_child_child_2[i]->setText(0, "Задачи " + QString::number(i + 1));
//         m_tree_child[i]->addChild(m_tree_child_child_2[i]);
//     }
//     m_tree_widget->addTopLevelItem(tree_item_1);

//     m_menu_layout->addWidget(m_tree_widget);
//     m_menu_box->setLayout(m_menu_layout);

//     m_text_box = new QGroupBox;
//     m_text_browser = new QTextBrowser(this);
//     m_text_browser->setMinimumSize(500, 500);

//     QFile file("html/begin_page.html");
//     if (!file.open(QIODevice::ReadOnly))
//     {
//         qWarning("file not found");
//     }
//     m_text_browser->setHtml(file.readAll());

//     connect(m_tree_widget, &QTreeWidget::itemClicked, this, &Help::setPage);

//     m_text_layout = new QGridLayout;
//     m_text_layout->addWidget(m_text_browser);
//     m_text_box->setLayout(m_text_layout);

//     m_main_layout = new QGridLayout;
//     m_main_layout->addWidget(m_tool_bar, 0, 0, 1, 2);
//     m_main_layout->addWidget(m_menu_box, 1, 0, 1, 1);
//     m_main_layout->addWidget(m_text_box, 1, 1, 1, 1);

//     setLayout(m_main_layout);
// }

// Help::~Help() {
// }

// void Help::showHelp() {
//     this->show();
// }

// void Help::buttonHide() {
//     this->hide();
// }

// void Help::buttonBack() {
//     this->hide();
// }

// void Help::buttonNetwork() {
//     QString link = "html/begin_page.html";
//     QDesktopServices::openUrl(QUrl(link));
// }

// void Help::actionShowContent() {
//     if(m_search_label != nullptr) {
//         delete m_search_label;
//         m_search_label = nullptr;
//     }
//     if(m_search_edit != nullptr) {
//         delete m_search_edit;
//         m_search_edit = nullptr;
//     }
//     if(m_search_button != nullptr) {
//         delete m_search_label;
//         m_search_label = nullptr;
//     }
//     if(m_result_edit != nullptr) {
//         delete m_result_edit;
//         m_result_edit = nullptr;
//     }

//     if(m_tree_pointer != nullptr) {
//         delete m_tree_pointer;
//         m_tree_pointer = nullptr;
//     }

//     if(m_tree_widget == nullptr) {
//         m_tree_widget = new QTreeWidget;
//         QTreeWidgetItem* tree_item_1 = new QTreeWidgetItem;
//         tree_item_1->setText(0, "Лабораторные работы");
//         for(int i = 0; i < 4; ++i) {
//             m_tree_child[i] = new QTreeWidgetItem();
//             m_tree_child[i]->setText(0, QString::number(i+1));
//             tree_item_1->addChild(m_tree_child[i]);
//             m_tree_child_child[i] = new QTreeWidgetItem;
//             m_tree_child_child_2[i] = new QTreeWidgetItem;
//             m_tree_child_child[i]->setText(0, "Цель " + QString::number(i + 1));
//             m_tree_child[i]->addChild(m_tree_child_child[i]);
//             m_tree_child_child_2[i]->setText(0, "Задачи " + QString::number(i + 1));
//             m_tree_child[i]->addChild(m_tree_child_child_2[i]);
//         }
//         m_tree_widget->addTopLevelItem(tree_item_1);
//         m_menu_layout->addWidget(m_tree_widget);
//         connect(m_tree_widget, &QTreeWidget::itemClicked, this, &Help::setPage);
//     }
// }

// void Help::actionShowPointer() {

//     if(m_tree_widget) {
//         delete m_tree_widget;
//         m_tree_widget = nullptr;
//     }

//     if(m_search_label != nullptr) {
//         delete m_search_label;
//         m_search_label = nullptr;
//     }
//     if(m_search_edit != nullptr) {
//         delete m_search_edit;
//         m_search_edit = nullptr;
//     }
//     if(m_search_button != nullptr) {
//         delete m_search_label;
//         m_search_label = nullptr;
//     }
//     if(m_result_edit != nullptr) {
//         delete m_result_edit;
//         m_result_edit = nullptr;
//     }

//     if(m_tree_pointer == nullptr) {
//         m_tree_pointer = new QTreeWidget;
//         for(int i = 0; i < 8; ++i) {
//             m_tree_child_pointer[i] = new QTreeWidgetItem();
//             if(i % 2 == 0)
//                 m_tree_child_pointer[i]->setText(0, "Цель " + QString::number(i / 2 + 1));
//             if(i % 2 != 0)
//                 m_tree_child_pointer[i]->setText(0, "Задачи " + QString::number(i / 2 + 1));
//             m_tree_pointer->addTopLevelItem(m_tree_child_pointer[i]);
//         }
//         m_menu_layout->addWidget(m_tree_pointer);
//         connect(m_tree_pointer, &QTreeWidget::itemClicked, this, &Help::setPage);
//     }
// }

// void Help::actionShowFind() {
//     if(m_tree_widget) {
//         delete m_tree_widget;
//         m_tree_widget = nullptr;
//     }

//     if(m_tree_pointer != nullptr) {
//         delete m_tree_pointer;
//         m_tree_pointer = nullptr;
//     }

//     if(m_search_label == nullptr)
//         m_search_label = new QLabel("Search text: ", this);
//     if(m_search_edit == nullptr)
//         m_search_edit = new QLineEdit(this);
//     if(m_search_button == nullptr)
//         m_search_button = new QPushButton("Search", this);
//     if(m_result_edit == nullptr)
//         m_result_edit = new QTextBrowser(this);
//     m_result_edit->setOpenLinks(false);

//     m_result_edit->setReadOnly(true);
//     m_menu_layout->addWidget(m_search_label);
//     m_menu_layout->addWidget(m_search_edit);
//     m_menu_layout->addWidget(m_search_button);
//     m_menu_layout->addWidget(m_result_edit);

//     connect(m_search_button, &QPushButton::clicked, this, &Help::performSearch);
//     connect(m_result_edit, &QTextBrowser::anchorClicked, this, &Help::onLinkClicked);
// }

// void Help::setPage(QTreeWidgetItem* item, int i) {
//     if(item->text(0).contains("Цель 1")) {
//         QFile file("html/lab_1_purpose.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
//     if(item->text(0).contains("Цель 2")) {
//         QFile file("html/lab_2_purpose.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
//     if(item->text(0).contains("Цель 3")) {
//         QFile file("html/lab_3_purpose.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
//     if(item->text(0).contains("Цель 4")) {
//         QFile file("html/lab_4_purpose.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }

//     if(item->text(0).contains("Задачи 1")) {
//         QFile file("html/lab_1_2.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
//     if(item->text(0).contains("Задачи 2")) {
//         QFile file("html/lab_2_2.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
//     if(item->text(0).contains("Задачи 3")) {
//         QFile file("html/lab_3_2.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
//     if(item->text(0).contains("Задачи 4")) {
//         QFile file("html/lab_4_2.html");
//         if (!file.open(QIODevice::ReadOnly))
//         {
//             qWarning("file not found");
//         }
//         m_text_browser->setHtml(file.readAll());
//     }
// }

// void Help::performSearch() {
//     QString directory_path = "html";
//     QString search_text = m_search_edit->text();

//     if(search_text.isEmpty()) {
//         return;
//     }

//     m_result_edit->clear();

//     QDir directory(directory_path);

//     QStringList filters;
//     filters << "*.html" << "*.htm";
//     QStringList files = directory.entryList(filters, QDir::Files);
//     foreach(const QString &filename, files) {
//         QString file_path = directory.filePath(filename);
//         QFile file(file_path);
//         if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//             QTextStream in(&file);
//             QString file_content = in.readAll();

//             QTextDocument document;
//             document.setHtml(file_content);
//             QString plain_text = document.toPlainText();
//             QStringList lines = plain_text.split('\n');

//             for (int i = 0; i < lines.size(); ++i) {
//                 if(lines[i].contains(search_text, Qt::CaseInsensitive)) {
//                     QString link = QString("<a href=\"%1#%2\">%3</a>").arg(file_path).arg(i + 1).arg(search_text);
//                     // QString link = QString("<a href=\"%1#%2\">%3 (line %4)</a>")
//                     //                    .arg(file_path)
//                     //                    .arg(i + 1)
//                     //                    .arg(filename)
//                     //                    .arg(i + 1);
//                     m_result_edit->append(link);
//                     m_result_edit->append(QString("Found in %1 at line %2: %3")
//                                               .arg(filename)
//                                               .arg(i + 1)
//                                               .arg(lines[i].trimmed()));
//                 }
//             }
//         }
//     }

//     if(m_result_edit->toPlainText().isEmpty()) {
//         m_result_edit->setText("No matches found.");
//     }
// }

// void Help::onLinkClicked(const QUrl &url) {
//     QString file_path = url.toLocalFile();
//     int line_number = url.fragment().toInt();

//     QFile file(file_path);
//     if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QTextStream in(&file);
//         QString file_content = in.readAll();

//         QTextDocument* document = new QTextDocument;
//         document->setHtml(file_content);

//         QTextCursor cursor(document);
//         cursor.movePosition(QTextCursor::Start);
//         for(int i = 1; i < line_number; ++i) {
//             cursor.movePosition(QTextCursor::Down);
//         }

//         cursor.select(QTextCursor::LineUnderCursor);
//         cursor.mergeCharFormat(QTextCharFormat());
//         QTextCharFormat highlight_format;
//         highlight_format.setBackground(Qt::yellow);
//         cursor.mergeCharFormat(highlight_format);

//         m_text_browser->setWindowTitle(file_path);
//         m_text_browser->setDocument(document);
//     }
//     m_text_browser->setText(file_path);
// }