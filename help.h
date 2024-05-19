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
};

#endif // HELP_H
