#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionstartThread_triggered()
{
    qDebug() << "...";
}


void MainWindow::on_actionstartDice_triggered()
{

}


void MainWindow::on_actionClose_triggered()
{

}


void MainWindow::on_actionClearText_triggered()
{

}


void MainWindow::on_actionStopThread_triggered()
{

}


void MainWindow::on_actionPauseDice_triggered()
{

}

