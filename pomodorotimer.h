#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

enum Level {WORK, SHORTBREAK, LONGBREAK};

#include <QObject>
#include "constants.h"

class PomodoroTimer : public QObject
{
    Q_OBJECT
public:
    explicit PomodoroTimer(QObject *parent = nullptr);
    void startPomodoroTimer();
    void stopPomodoroTimer();
    void setdurationOfWork(int const& durationOfWork);
    void setdurationOfShortBreak(int const& durationOfShortBreak);
    void setdurationOfLongBreak(int const& durationOfLongBreak);
protected:
    void timerEvent(QTimerEvent *event);
private:
   int timeInterval;
   int idTimer;
   int durationOfWork;
   int durationOfShortBreak;
   int durationOfLongBreak;
   int counter;
   int numberOfPomidor;
   Level currentPeriod;

   void handleBreak(int timeOfBreak);
signals:

   void persentOfWork(int p);
   void persentOfBreak(int p);

public slots:
};

#endif // POMODOROTIMER_H
