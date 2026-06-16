#include "threaddice.h"
#include <QRandomGenerator>

ThreadDice::ThreadDice(QObject *parent)
    : QThread{parent}
{}

void ThreadDice::run() {
    while (!m_threadStop) {
        if (!m_dicePause) {
            m_diceValue = QRandomGenerator::global()->bounded(1,7);
            emit sigDiceValueChanged(m_diceValue);
        }
        msleep(500);
    }
    quit();
}

void ThreadDice::slotStopThread() {
    m_threadStop = true;
}

void ThreadDice::slotStartDice() {
    m_dicePause = false;
}

void ThreadDice::slotPauseDice() {
    m_dicePause = true;
}

