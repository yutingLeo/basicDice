#ifndef THREADDICE_H
#define THREADDICE_H

#include <QThread>

class ThreadDice : public QThread
{
    Q_OBJECT
public:
    explicit ThreadDice(QObject *parent = nullptr);
    void run() override;
public slots:
    void slotStopThread();
    void slotStartDice();
    void slotPauseDice();
signals:
    void sigDiceValueChanged(quint8 diceValue);
private:
    bool m_threadStop = false;
    bool m_dicePause = true;
    quint8 m_diceValue = 0;
};

#endif // THREADDICE_H
