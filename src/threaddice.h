#ifndef THREADDICE_H
#define THREADDICE_H

#include <QThread>
#include <QMutex>

struct Dice
{
    static quint64 seq;
    quint8  diceValue;
};

class ThreadDice : public QThread
{
    Q_OBJECT
public:
    explicit ThreadDice(QObject *parent = nullptr);
    void run() override;
    void resetAllFlags();
public slots:
    void slotStopThread();
    void slotStartDice();
    void slotPauseDice();
signals:
    void sigDiceValueChanged(Dice diceValue);
private:
    bool m_threadStop = false;
    bool m_dicePause = true;
    QMutex m_mutex;
    Dice m_diceValue = {0};
};

#endif // THREADDICE_H
