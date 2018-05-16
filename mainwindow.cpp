#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mPomodoroTimer(new PomodoroTimer),
    mWndSettings(new Settings),
    mPlayer(new QMediaPlayer(this))
{
    ui->setupUi(this);

    SettingsSaver::getInstance().loadSettings("./Data.json");

    initPomodoroTimer();

    QObject::connect(mWndSettings, SIGNAL(newData(Data)), this, SLOT(setNewData(Data)));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete mPomodoroTimer;

    delete mWndSettings;

    delete mPlayer;
}

void MainWindow::on_pushButton_settings_clicked()
{
    this->mWndSettings->show();
    this->mWndSettings->setData(SettingsSaver::getInstance().getData());
}

void MainWindow::on_pushButton_timeStart_clicked()
{
    this->mPomodoroTimer->startPomodoroTimer();

    mPlayer->setMedia(QUrl(SettingsSaver::getInstance().getData().getPathToMelodyOfTick()));
    mPlayer->setVolume(SettingsSaver::getInstance().getData().getVolumeOfTick().toInt());
    mPlayer->play();
}

void MainWindow::on_pushButton_timeStop_clicked()
{
    this->mPomodoroTimer->stopPomodoroTimer();

    this->ui->progressBar_work->setValue(0);

    this->ui->progressBar_break->setValue(0);

    mPlayer->stop();
}

void MainWindow::set_Persent_of_work(int p)
{
    this->ui->progressBar_work->setValue(p);

    if(100 == p)
    {
        mPlayer->stop();
        mPlayer->setMedia(QUrl(SettingsSaver::getInstance().getData().getPathToMelodyOfRing()));
        mPlayer->setVolume(SettingsSaver::getInstance().getData().getVolumeOfRing().toInt());
        mPlayer->play();
    }
}

void MainWindow::set_Persent_of_break(int p)
{
    this->ui->progressBar_break->setValue(p);

    if(100 == p)
    {
        mPlayer->stop();
        mPlayer->setMedia(QUrl(SettingsSaver::getInstance().getData().getPathToMelodyOfTick()));
        mPlayer->setVolume(SettingsSaver::getInstance().getData().getVolumeOfTick().toInt());
        mPlayer->play();
    }
}

void MainWindow::initPomodoroTimer()
{
    mPomodoroTimer->setdurationOfWork(SettingsSaver::getInstance().getData().getDurationOfWork().toInt());
    mPomodoroTimer->setdurationOfShortBreak(SettingsSaver::getInstance().getData().getDurationOfShortBreak().toInt());
    mPomodoroTimer->setdurationOfLongBreak(SettingsSaver::getInstance().getData().getDurationOfLongBreak().toInt());

    QObject::connect(mPomodoroTimer, SIGNAL(persentOfWork(int)), this, SLOT(set_Persent_of_work(int)));
    QObject::connect(mPomodoroTimer, SIGNAL(persentOfBreak(int)), this, SLOT(set_Persent_of_break(int)));
}

void MainWindow::setNewData(Data d)
{
    SettingsSaver::getInstance().setData(d);

    SettingsSaver::getInstance().saveSettings("./Data.json");
}
