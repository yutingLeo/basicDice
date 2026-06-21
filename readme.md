baseed on the thread example of Qt6C++PraogrmmingGuide, a book about how to use Qt to develop.
mainly fixed:
  - add QMutex to protect DiceThread's member variables
  - in main GUI thread, use signal-slot transfer the command to operate thread start/stop, the
    operate dice running/pause instead of directly call the thread's member functions
  - rewrite exit code about the run() sub thread exit, except from set stopFlag, add call QThr\
    ead::requestInterruption(), and check isInterruptionRequested() in run() loop.