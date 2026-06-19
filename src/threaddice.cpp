#include "threaddice.h"
#include <QRandomGenerator>

quint64 Dice::seq = 0;

ThreadDice::ThreadDice(QObject *parent)
    : QThread{parent}
{}

void ThreadDice::run() {
    while (true) {
        bool threadStop, dicePause;
        {
            QMutexLocker lock(&m_mutex);
            threadStop = m_threadStop;
            dicePause = m_dicePause;
        }
        if (threadStop || isInterruptionRequested()) break;
        if (!dicePause) {
            m_diceValue.diceValue = QRandomGenerator::global()->bounded(1,7);
            m_diceValue.seq++;
            emit sigDiceValueChanged(m_diceValue);
        }
        msleep(500);
    }
    quit();
}

void ThreadDice::resetAllFlags() {
    QMutexLocker lock(&m_mutex);
    m_threadStop = false;
    m_dicePause = true;
}

void ThreadDice::slotStopThread() {
    QMutexLocker lock(&m_mutex);
    m_threadStop = true;
}

void ThreadDice::slotStartDice() {
    QMutexLocker lock(&m_mutex);
    m_dicePause = false;
}

void ThreadDice::slotPauseDice() {
    QMutexLocker lock(&m_mutex);
    m_dicePause = true;
}

