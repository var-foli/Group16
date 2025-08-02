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
#include "skipList.h"
#include <chrono>

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

    //qDebug() << "Current working directory:" << QDir::currentPath();
    games = parseCSV("./data/games.csv");

    ui->tableWidget_data->setRowCount(games.size());
    for(int i = 0; i < games.size(); ++i){
        ui->tableWidget_data->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(games[i].title)));
        ui->tableWidget_data->setItem(i, 1, new QTableWidgetItem(QString::number(games[i].completion, 'f', 2) + QString::fromStdString(" hrs")));
        ui->tableWidget_data->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(Game::vectorToStr(games[i].genres))));
        ui->tableWidget_data->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(games[i].release)));
        ui->tableWidget_data->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(Game::vectorToStr(games[i].platforms))));
        ui->tableWidget_data->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(Game::vectorToStr(games[i].publisher))));

        tree.insert(prefixTreeHead, games[i].title, games[i].title, games[i].completion, games[i].genres, games[i].release, games[i].platforms, games[i].publisher);
        skiplist.insert(games[i]);
    }

    ui->tableWidget_data->resizeRowsToContents();
    ui->tableWidget_data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_data->setSortingEnabled(true);
    ui->tableWidget_data->setAlternatingRowColors(true);
    ui->tableWidget_data->verticalHeader()->setVisible(false);

    ui->searchToggle->setText(QString::fromStdString("Switch to Skip List"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_txtSearchBox_returnPressed()
{
    std::string input = ui->txtSearchBox->text().toStdString();

    resetTable();
    if(input.empty()) return;

    // PREFIX TREE IMPLEMENTATION
    if(prefixSearch){
        auto start = std::chrono::high_resolution_clock::now();
        // Access prefix tree
        // Enter input into prefix tree search function and get a node back
        tuple output = tree.searchName(prefixTreeHead, input);
        int resultSize = get<0>(output).size();
        if(resultSize == 0) {
            hideTable();
            return;
        }
        // This returns multiple items with the search term in their title
        // Clear table view
        for(int i = 0; i < games.size(); ++i){
            bool matching = false;
            for(int j = 0; j < resultSize; ++j){
                if(ui->tableWidget_data->item(i, 0)->text().toStdString() == get<0>(output)[j]) matching = true;
            }

            if(matching) continue;
            ui->tableWidget_data->setRowHidden(i, true);
        }
        // Display only that node in the table
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        cout << "Prefix Tree duration: " << duration.count() << " ms" << endl;
    }
    else{
        // SKIP LIST IMPLEMENTATION
        auto start = std::chrono::high_resolution_clock::now();
        const Node* result = skiplist.search(input);
        if (!result) {
            hideTable();
            cout << "No result" << endl;
            return;
        }

        for (int i = 0; i < games.size(); ++i) {
            if (games[i].title == result->title) {
                ui->tableWidget_data->setRowHidden(i, false);
            } else {
                ui->tableWidget_data->setRowHidden(i, true);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        cout << "Skip list duration: " << duration.count() << " ms" << endl;
    }

}

void MainWindow::resetTable()
{
    for(int i = 0; i < games.size(); ++i){
        ui->tableWidget_data->setRowHidden(i, false);
    }
}

void MainWindow::hideTable()
{
    for(int i = 0; i < games.size(); ++i){
        ui->tableWidget_data->setRowHidden(i, true);
    }
}


void MainWindow::on_searchToggle_clicked()
{
    prefixSearch = !prefixSearch;
    ui->searchToggle->setText(QString::fromStdString(prefixSearch ? "Switch to Skip List" : "Switch to Prefix Tree"));
}

void MainWindow::on_resetButton_clicked()
{
    resetTable();
    ui->tableWidget_data->clearFocus();
    ui->tableWidget_data->clearSelection();
    ui->txtSearchBox->clear();
    ui->txtSearchBox->clearFocus();
}

