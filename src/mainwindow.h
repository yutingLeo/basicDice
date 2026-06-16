#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_actionstartThread_triggered();

    void on_actionstartDice_triggered();

    void on_actionClose_triggered();

    void on_actionClearText_triggered();

    void on_actionStopThread_triggered();

    void on_actionPauseDice_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
