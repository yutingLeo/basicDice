#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threaddice.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void slotDiceValueChanged(Dice diceVal);
    void slotThreadStarted();
    void slotThreadFinished();
    void on_actionstartThread_triggered();
    void on_actionstartDice_triggered();
    void on_actionClearText_triggered();
    void on_actionStopThread_triggered();
    void on_actionPauseDice_triggered();

signals:
    void sigStopThread();
    void sigStartDice();
    void sigPauseDice();

private:
    void displayDiceText(Dice dice);
    void displayDicePixmap(Dice dice);
    Ui::MainWindow *ui;
    ThreadDice m_diceThread;
    QString m_showText;
    QList<QPixmap> m_pixmapList;
};
#endif // MAINWINDOW_H
