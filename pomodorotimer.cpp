#include "pomodorotimer.h"

PomodoroTimer::PomodoroTimer(QObject *parent) : QObject(parent)
{
    PomodoroTimer::timeInterval = TIMERINTERVAL;

    durationOfWork = DEFAULT_VALUE;
    durationOfShortBreak = DEFAULT_VALUE;
    durationOfLongBreak = DEFAULT_VALUE;
    counter = DEFAULT_VALUE;
    numberOfPomidor = DEFAULT_VALUE;
    currentPeriod = Level::WORK;
}

void PomodoroTimer::startPomodoroTimer()
{
    PomodoroTimer::idTimer = PomodoroTimer::startTimer(PomodoroTimer::timeInterval);
}

void PomodoroTimer::stopPomodoroTimer()
{
    PomodoroTimer::killTimer(PomodoroTimer::idTimer);

    counter = DEFAULT_VALUE;
    numberOfPomidor = DEFAULT_VALUE;
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
        emit persentOfBreak(ZERO_PERSENT);

        if(counter < durationOfWork)
        {
            int temp = int(double(counter) / durationOfWork * HUNDRED_PERSENT);

            emit persentOfWork(temp);
        }
        else if(counter == durationOfWork)
        {
            emit persentOfWork(HUNDRED_PERSENT);

            ++numberOfPomidor;

            if(COUNTOFPOMODORO == numberOfPomidor)
            {
                numberOfPomidor = DEFAULT_VALUE;

                currentPeriod = Level::LONGBREAK;
            }
            else
            {
                currentPeriod = Level::SHORTBREAK;
            }

            counter = DEFAULT_VALUE;
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
    emit persentOfWork(ZERO_PERSENT);

    if(counter < timeOfBreak)
    {
        emit persentOfBreak(int(double(counter) / timeOfBreak * HUNDRED_PERSENT));
    }
    else if(counter == timeOfBreak)
    {
        emit persentOfBreak(HUNDRED_PERSENT);

        currentPeriod = Level::WORK;

        counter = DEFAULT_VALUE;
    }
}
