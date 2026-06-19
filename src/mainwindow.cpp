#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // bind connections: this.command -> thead.slot
    connect(this, &MainWindow::sigStopThread, &m_diceThread, &ThreadDice::slotStopThread);
    connect(this, &MainWindow::sigStartDice, &m_diceThread, &ThreadDice::slotStartDice);
    connect(this, &MainWindow::sigPauseDice, &m_diceThread, &ThreadDice::slotPauseDice);

    // bind connections: thread.state -> this.display
    connect(&m_diceThread, &ThreadDice::sigDiceValueChanged, this, &MainWindow::slotDiceValueChanged);
    connect(&m_diceThread, &ThreadDice::started, this, &MainWindow::slotThreadStarted);
    connect(&m_diceThread, &ThreadDice::finished, this, &MainWindow::slotThreadFinished);

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
    m_diceThread.resetAllFlags();
    m_diceThread.start();
}

void MainWindow::on_actionStopThread_triggered()
{
    emit sigStopThread();
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
        // 1. 设置自定义业务停止标记，业务循环感知退出
        emit sigStopThread();
        // 2. 请求内置中断，立刻唤醒msleep阻塞，加速退出
        m_diceThread.requestInterruption();
    }
    // 先给1秒时间正常优雅退出
    bool exited = m_diceThread.wait(1000);
    if (!exited) {
        // 超时未正常退出，强制杀死线程
        m_diceThread.terminate();
        // 必须等待内核回收线程资源，防止崩溃、内存泄漏
        m_diceThread.wait();
    }
    event->accept();
}

void MainWindow::on_actionClearText_triggered()
{
    m_showText.clear();
    ui->plainTextEdit->clear();
}

void MainWindow::slotDiceValueChanged(quint8 diceVal) {
    if (diceVal >= 1 and diceVal <= 6) {
        displayDiceText(diceVal);
        displayDicePixmap(diceVal);
    }
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

void MainWindow::slotThreadStarted() {
    ui->actionstartThread->setEnabled(false);
    ui->actionStopThread->setEnabled(true);
    ui->actionstartDice->setEnabled(true);
    ui->actionPauseDice->setEnabled(false);
}

void MainWindow::slotThreadFinished() {
    ui->actionStopThread->setEnabled(false);
    ui->actionstartDice->setEnabled(false);
    ui->actionPauseDice->setEnabled(false);
    ui->actionstartThread->setEnabled(true);
}
