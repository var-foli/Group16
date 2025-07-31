#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include "game.h"
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "ParseCSV.h"
#include "prefix.h"
#include <QDir>
#include <QDebug>
#include <iostream>

QStandardItemModel* createModel(int rows, int cols){
    QStandardItemModel* model = new QStandardItemModel(rows, cols);
    QStringList headers = {"Name", "Completion Time", "Genre(s)", "Release Date", "Platform(s)", "Publisher(s)"};
    model->setHorizontalHeaderLabels(headers);
    return model;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // qDebug() << "Current working directory:" << QDir::currentPath();
    vector<Node> games = parseCSV("./data/games - Copy.csv");

    QStandardItemModel* model = createModel(0, 6);
    ui->tableView_data->setModel(model);

    for(int i = 0; i < games.size(); i++){
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(games[i].title));
        row << new QStandardItem(QString::fromStdString(to_string(games[i].completion)));
        row << new QStandardItem(QString::fromStdString(Game::vectorToStr(games[i].genres)));
        row << new QStandardItem(QString::fromStdString(games[i].release));
        row << new QStandardItem(QString::fromStdString(Game::vectorToStr(games[i].platforms)));
        row << new QStandardItem(QString::fromStdString(Game::vectorToStr(games[i].publisher)));

        PrefixNode* node = new PrefixNode();
        tree.insert(node, games[i].title, games[i].title, games[i].completion, games[i].genres, games[i].release, games[i].platforms, games[i].publisher);

        model->appendRow(row);
    }

    ui->tableView_data->resizeRowsToContents();
    ui->tableView_data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_data->setSortingEnabled(true);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView_data->setModel(proxyModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_txtSearchBox_textChanged(const QString &arg1)
{
    // This is the built-in search filter functionality. Do we need to replace it with our own implementation?
    // proxyModel->setFilterKeyColumn(0);
    // proxyModel->setFilterFixedString(arg1);
    // ui->tableView_data->resizeRowsToContents();
}


void MainWindow::on_txtSearchBox_returnPressed()
{
    std::string input = ui->txtSearchBox->text().toStdString();
    cout << "Search: " << input << endl;

    // Access prefix tree
    // Enter input into prefix tree search function and get a node back
    PrefixNode* node = new PrefixNode();
    tuple output = tree.searchName(node, input);

    vector<string> title = get<0>(output);
    for(const string& s : title){
        cout << s << endl;
    }
    // Display only that node in the table
}

