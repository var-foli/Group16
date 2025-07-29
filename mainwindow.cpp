#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>
#include "testgameclass.h"
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

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

    // API call to Kaggle to get the datasets

    int numRows = 10;
    QStandardItemModel* model = createModel(0, 6);
    ui->tableView_data->setModel(model);

    for(int i = 0; i < numRows; ++i){
        QList<QStandardItem*> row;
        TestGameClass game("GoW " + std::to_string(i+1),
                           std::to_string(10 + i) + " hrs",
                           {"Action","Adventure","Hack and Slash"},
                           std::to_string(2010 + i),
                           {"Playstation 4", "PC"},
                           {"SCEA"});
        row << new QStandardItem(QString::fromStdString(game.name));
        row << new QStandardItem(QString::fromStdString(game.avgDuration));
        row << new QStandardItem(QString::fromStdString(game.genres));
        row << new QStandardItem(QString::fromStdString(game.releaseDate));
        row << new QStandardItem(QString::fromStdString(game.platforms));
        row << new QStandardItem(QString::fromStdString(game.publishers));

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
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterFixedString(arg1);
    ui->tableView_data->resizeRowsToContents();
}

