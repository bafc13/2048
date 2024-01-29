#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QMessageBox::StandardButton message = QMessageBox::question(this, "Chose play mode?!", "You want to play default 4x4 mode?", QMessageBox::Yes | QMessageBox::No);
    if(message == QMessageBox::Yes){
        board = new boardWithgame(this);
        board->show();
    } else {
        message = QMessageBox::question(this, "Chose play mode?!", "Ok, maybe 5x5??", QMessageBox::Yes | QMessageBox::No);
        if(message == QMessageBox::Yes){
            board5 = new board5x5;
            board5->show();
        } else {
            //message = QMessageBox::about(this, "Ok", "Sorry, w8t for updates or chose supported play mode!");
        }
    }

}

void MainWindow::on_scoreButton_clicked()
{
    fin.open(name.toStdString());
    while(std::getline(fin,line)){
        if(std::stoi(line) > maxScore){
            maxScore = std::stoi(line);
        }
    }
    line = std::to_string(maxScore);
    QMessageBox *mes = new QMessageBox;
    mes->setText(QString::fromStdString(line));
    mes->exec();
    fin.close();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

