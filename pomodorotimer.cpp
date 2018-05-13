#include "pomodorotimer.h"

PomodoroTimer::PomodoroTimer(QObject *parent) : QObject(parent)
{
    PomodoroTimer::timeInterval = TIMERINTERVAL;

    durationOfWork = 0;
    durationOfShortBreak = 0;
    durationOfLongBreak = 0;
    counter = 0;
    numberOfPomidor = 0;
    currentPeriod = Level::WORK;
}

void PomodoroTimer::startPomodoroTimer()
{
    PomodoroTimer::idTimer = PomodoroTimer::startTimer(PomodoroTimer::timeInterval);
}

void PomodoroTimer::stopPomodoroTimer()
{
    PomodoroTimer::killTimer(PomodoroTimer::idTimer);

    counter = 0;
    numberOfPomidor = 0;
    currentPeriod = Level::WORK;
}

void PomodoroTimer::setdurationOfWork(int const& durationOfWork)
{
    this->durationOfWork = durationOfWork;
}

void PomodoroTimer::setdurationOfShortBreak(int const& durationOfShortBreak)
{
    this->durationOfShortBreak = durationOfShortBreak;
}

void PomodoroTimer::setdurationOfLongBreak(int const& durationOfLongBreak)
{
    this->durationOfLongBreak = durationOfLongBreak;
}

void PomodoroTimer::timerEvent(QTimerEvent *event)
{
    ++counter;

    if(Level::WORK == currentPeriod)
    {
        emit persentOfBreak(0);

        if(counter < durationOfWork)
        {
            int temp = int(double(counter) / durationOfWork * 100);

            emit persentOfWork(temp);
        }
        else if(counter == durationOfWork)
        {
            emit persentOfWork(100);

            ++numberOfPomidor;

            if(COUNTOFPOMODORO == numberOfPomidor)
            {
                numberOfPomidor = 0;

                currentPeriod = Level::LONGBREAK;
            }
            else
            {
                currentPeriod = Level::SHORTBREAK;
            }

            counter = 0;
        }
    }
    else if(Level::SHORTBREAK == currentPeriod)
    {
        handleBreak(durationOfShortBreak);
    }
    else if(Level::LONGBREAK == currentPeriod)
    {
        handleBreak(durationOfLongBreak);
    }
}

void PomodoroTimer::handleBreak(int timeOfBreak)
{
    emit persentOfWork(0);

    if(counter < timeOfBreak)
    {
        emit persentOfBreak(int(double(counter) / timeOfBreak * 100));
    }
    else if(counter == timeOfBreak)
    {
        emit persentOfBreak(100);

        currentPeriod = Level::WORK;

        counter = 0;
    }
}
