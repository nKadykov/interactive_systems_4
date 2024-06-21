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

    m_tab_widget = new QTabWidget;

    m_tab_1 = new QWidget;
    m_tab_2 = new QWidget;
    m_tab_3 = new QWidget;

    m_tab_1_layout = new QVBoxLayout(m_tab_1);
    m_tab_2_layout = new QVBoxLayout(m_tab_2);
    m_tab_3_layout = new QVBoxLayout(m_tab_3);

    m_tab_widget->addTab(m_tab_1, "Content");
    m_tab_widget->addTab(m_tab_2, "Template");
    m_tab_widget->addTab(m_tab_3, "Character");
    connect(m_tab_widget, &QTabWidget::currentChanged, this, [=](int index) {
        if(index == 1) {
            m_template_edit->setFocus();
        } else if (index == 2) {
            m_character_edit->setFocus();
        }
    });

    m_menu_layout->addWidget(m_tab_widget);
    m_menu_box->setLayout(m_menu_layout);

    m_text_box = new QGroupBox;
    m_text_browser = new QTextBrowser(this);
    m_text_browser->setMinimumSize(500, 500);

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
    m_tab_1_layout->addWidget(m_tree_widget);
    m_menu_box->setLayout(m_tab_1_layout);

    m_template_edit = new QLineEdit;
    connect(m_template_edit, &QLineEdit::returnPressed, this, &Help::templateSearch);
    m_tab_2_layout->addWidget(m_template_edit);
    m_menu_box->setLayout(m_tab_2_layout);

    m_character_edit = new QLineEdit;
    connect(m_character_edit, &QLineEdit::textChanged, this, &Help::characterSearch);
    m_tab_3_layout->addWidget(m_character_edit);
    m_words_list = new QListWidget;
    connect(m_words_list, &QListWidget::itemClicked, this, &Help::highlightWords);
    m_tab_3_layout->addWidget(m_words_list);
    m_menu_box->setLayout(m_tab_3_layout);

    QFile file("html/lab_1_2.html");
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

void Help::templateSearch() {
    QString word = m_template_edit->text();
    if(word.isEmpty()) {
        return;
    }
    QTextDocument* doc = m_text_browser->document();
    QTextCursor cursor(doc);

    QTextCharFormat default_format;
    default_format.setBackground(Qt::white);

    cursor.movePosition(QTextCursor::Start);
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        QTextCharFormat char_format = cursor.charFormat();
        if(!char_format.isAnchor()) {
            cursor.mergeCharFormat(default_format);
        }
    }

    m_text_browser->moveCursor(QTextCursor::Start);
    QTextCharFormat format;
    format.setBackground(Qt::yellow);

    cursor = QTextCursor(doc);
    while(!cursor.isNull() && !cursor.atEnd()) {
        cursor = m_text_browser->document()->find(word, cursor);
        if(!cursor.isNull()) {
            cursor.mergeCharFormat(format);
        }
    }
}

void Help::characterSearch() {
    QString text = m_character_edit->text();
    if(text.isEmpty()) {
        return;
    }
    m_words_list->clear();
    QTextDocument *doc = m_text_browser->document();
    QTextCursor cursor(doc);
    // QRegularExpression regex(text + "\\w*", QRegularExpression::CaseInsensitiveOption);



    QSet<QString> unique_words;
    cursor.movePosition(QTextCursor::Start);

    while(!cursor.isNull() && !cursor.atEnd()) {
        // cursor = doc->find(regex, cursor);
        // cursor = doc->find(text, cursor, QTextDocument::FindCaseSensitively);
        // if(!cursor.isNull()) {
        //     QString word = cursor.selectedText();
        //     if(word.startsWith(text, Qt::CaseInsensitive)) {
        //         cursor.select(QTextCursor::WordUnderCursor);
        //         word = cursor.selectedText();
        //         if (!unique_words.contains(word)) {
        //             unique_words.insert(word);
        //             QListWidgetItem *item = new QListWidgetItem(word);
        //             m_words_list->addItem(item);
        //         }
        //     }
        //     cursor.movePosition(QTextCursor::NextWord);
        // }
        cursor.movePosition(QTextCursor::NextWord);
        cursor.select(QTextCursor::WordUnderCursor);

        QString word = cursor.selectedText();
        // Проверка, что слово начинается с введенного текста
        if (word.startsWith(text, Qt::CaseSensitive) && !unique_words.contains(word)) {
            unique_words.insert(word);
            QListWidgetItem *item = new QListWidgetItem(word);
            m_words_list->addItem(item);
        }
    }
}

void Help::keyPressEvent(QKeyEvent *event) {
    if(event->key()) {
        event->ignore();
    }
    if(event->key() == Qt::Key_Left) {
        int current_index = m_tab_widget->currentIndex();
        int new_index = (current_index == 0) ? m_tab_widget->count() - 1 : current_index - 1;
        m_tab_widget->setCurrentIndex(new_index);
    } else if (event->key() == Qt::Key_Right) {
        int current_index = m_tab_widget->currentIndex();
        int new_index = (current_index == m_tab_widget->count() - 1) ? 0 : current_index + 1;
        m_tab_widget->setCurrentIndex(new_index);
    }
}

void Help::highlightWords(QListWidgetItem* item) {
    QString word = item->text();

    QTextDocument* doc = m_text_browser->document();
    QTextCursor cursor(doc);

    QTextCharFormat default_format;
    default_format.setBackground(Qt::white);

    cursor.movePosition(QTextCursor::Start);
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        QTextCharFormat char_format = cursor.charFormat();
        if(!char_format.isAnchor()) {
            cursor.mergeCharFormat(default_format);
        }
    }

    cursor = QTextCursor(doc);

    QTextCharFormat format;
    format.setBackground(Qt::yellow);

    while(!cursor.isNull() && !cursor.atEnd()) {
        cursor = doc->find(word, cursor, QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
        if(!cursor.isNull()) {
            cursor.mergeCharFormat(format);
        }
    }
}
