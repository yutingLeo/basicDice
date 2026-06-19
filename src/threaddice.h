#ifndef THREADDICE_H
#define THREADDICE_H

#include <QThread>
#include <QMutex>

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
    void sigDiceValueChanged(quint8 diceValue);
private:
    bool m_threadStop = false;
    bool m_dicePause = true;
    QMutex m_mutex;
    quint8 m_diceValue = 0;
};

#endif // THREADDICE_H
