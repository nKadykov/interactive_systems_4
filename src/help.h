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

    void actionShowContent();
    void actionShowPointer();
    void actionShowFind();

    void setPage(QTreeWidgetItem*, int);

    void performSearch();
    void onLinkClicked(QListWidgetItem*);
private:
    QToolBar* m_tool_bar;
    QGroupBox* m_menu_box;
    QGroupBox* m_text_box;

    QMenu* m_menu_content;
    QMenu* m_menu_pointer;
    QMenu* m_menu_find;
    QMenuBar* m_menu_bar;

    QTreeWidget* m_tree_widget;

    QGridLayout* m_main_layout;
    QGridLayout* m_menu_layout;
    QGridLayout* m_text_layout;
    enum {NUMBER = 3};
    QPushButton* m_buttons[NUMBER];
    QTextBrowser* m_text_browser;

    QAction* m_action_content;
    QAction* m_action_pointer;
    QAction* m_action_find;
    enum {CHILDS = 4};
    QTreeWidgetItem* m_tree_child[CHILDS];
    QTreeWidgetItem* m_tree_child_child[CHILDS];
    QTreeWidgetItem* m_tree_child_child_2[CHILDS];

    QLabel* m_search_label = nullptr;
    QPushButton* m_search_button = nullptr;
    QLineEdit* m_search_edit = nullptr;
    QListWidget* m_file_list = nullptr;

    QTreeWidget* m_tree_pointer = nullptr;
    enum{POINTERS = 8};
    QTreeWidgetItem* m_tree_child_pointer[POINTERS];

    QString m_search_text = "";
};

#endif // HELP_H