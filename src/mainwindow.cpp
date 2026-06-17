#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // bind connections
    connect(this, &MainWindow::sigStopThread, &m_diceThread, &ThreadDice::slotStopThread);
    connect(this, &MainWindow::sigStartDice, &m_diceThread, &ThreadDice::slotStartDice);
    connect(this, &MainWindow::sigPauseDice, &m_diceThread, &ThreadDice::slotPauseDice);
    connect(&m_diceThread, &ThreadDice::sigDiceValueChanged, this, &MainWindow::slotDiceValueChanged);

    // action button state management
    ui->actionstartThread->setEnabled(true);
    ui->actionStopThread->setEnabled(false);
    ui->actionstartDice->setEnabled(false);
    ui->actionPauseDice->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionstartThread_triggered()
{
    m_diceThread.start();
    ui->actionstartThread->setEnabled(false);
    ui->actionStopThread->setEnabled(true);
    ui->actionstartDice->setEnabled(true);
    ui->actionPauseDice->setEnabled(false);
}

void MainWindow::on_actionStopThread_triggered()
{
    if (m_diceThread.isRunning()) {
        emit sigStopThread();
    }
    ui->actionStopThread->setEnabled(false);
    ui->actionstartDice->setEnabled(false);
    ui->actionPauseDice->setEnabled(false);
    ui->actionstartThread->setEnabled(true);
}

void MainWindow::on_actionstartDice_triggered()
{
    if (m_diceThread.isRunning()) {
        emit sigStartDice();
    }
    ui->actionstartDice->setEnabled(false);
    ui->actionPauseDice->setEnabled(true);
}

void MainWindow::on_actionPauseDice_triggered()
{
    emit sigPauseDice();
    ui->actionstartDice->setEnabled(true);
    ui->actionPauseDice->setEnabled(false);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (m_diceThread.isRunning()) {
        emit sigStopThread();
    }
    bool exited = m_diceThread.wait(500);
    if (!exited) {
        m_diceThread.terminate();
    }
    event->accept();
}

void MainWindow::on_actionClearText_triggered()
{
    m_showText.clear();
    ui->plainTextEdit->clear();
}

void MainWindow::slotDiceValueChanged(quint8 diceVal) {
    // 是否越界
    if (diceVal < 1 || diceVal > 6) return;
    // 显示
    displayDiceText(diceVal);
    displayDicePixmap(diceVal);
}

void MainWindow::displayDiceText(quint8 diceVal) {
    QString curText = QString("第 n 次掷骰子，点数为：%1\n").arg(diceVal);
    m_showText.append(curText);
    ui->plainTextEdit->setPlainText(m_showText);
}

void MainWindow::displayDicePixmap(quint8 diceVal) {
    QString pixFileName = QString(":/dice/images/d%1.jpg").arg(diceVal);
    QPixmap pixmap(pixFileName);
    ui->lblPic->setPixmap(pixmap);
}
