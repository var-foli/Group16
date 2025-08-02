#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "prefix.h"
#include "skipList.h"
#include "ParseCSV.h"

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
    void on_txtSearchBox_returnPressed();

    void on_searchToggle_clicked();

    void on_resetButton_clicked();

private:
    bool prefixSearch = true;
    vector<Node> games;
    PrefixNode* prefixTreeHead = new PrefixNode();
    PrefixTree tree;
    SkipList skiplist;
    Ui::MainWindow *ui;
    QSortFilterProxyModel* proxyModel;
    void resetTable();
    void hideTable();
};
#endif // MAINWINDOW_H
