#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QGridLayout>
#include <QGroupBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QTextBrowser>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QTabWidget>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

class Help : public QDialog
{
    Q_OBJECT
public:
    Help(QWidget* parent = nullptr);
    ~Help();
    void showHelp();

private slots:
    void buttonHide();
    void buttonBack();
    void buttonNetwork();

    void setPage(QTreeWidgetItem*, int);

    // void performSearch();
    // void onLinkClicked(QListWidgetItem*);

    void templateSearch();
    void characterSearch();
    void highlightWords(QListWidgetItem* item);

    void keyPressEvent(QKeyEvent *event) override;
private:
    QToolBar* m_tool_bar;
    QGroupBox* m_menu_box;
    QGroupBox* m_text_box;

    QTreeWidget* m_tree_widget;

    QGridLayout* m_main_layout;
    QGridLayout* m_menu_layout;
    QGridLayout* m_text_layout;
    enum {NUMBER = 3};
    QPushButton* m_buttons[NUMBER];

    QTextBrowser* m_text_browser;

    QTabWidget* m_tab_widget;
    QWidget* m_tab_1;
    QWidget* m_tab_2;
    QWidget* m_tab_3;

    QVBoxLayout* m_tab_1_layout;
    QVBoxLayout* m_tab_2_layout;
    QVBoxLayout* m_tab_3_layout;

    enum {CHILDS = 4};
    QTreeWidgetItem* m_tree_child[CHILDS];
    QTreeWidgetItem* m_tree_child_child[CHILDS];
    QTreeWidgetItem* m_tree_child_child_2[CHILDS];

    // QLabel* m_search_label = nullptr;
    // QPushButton* m_search_button = nullptr;
    // QLineEdit* m_search_edit = nullptr;
    // QListWidget* m_file_list = nullptr;

    // QTreeWidget* m_tree_pointer = nullptr;
    // enum{POINTERS = 8};
    // QTreeWidgetItem* m_tree_child_pointer[POINTERS];

    QLineEdit* m_template_edit = nullptr;
    QLineEdit* m_character_edit = nullptr;
    QListWidget* m_words_list = nullptr;

    QString m_search_text = "";
};

#endif // HELP_H
