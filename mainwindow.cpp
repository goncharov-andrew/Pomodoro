#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pomodoroTimer(new PomodoroTimer),    
    mWndSettings(new Settings),
    m_player(new QMediaPlayer(this))
{
    ui->setupUi(this);

    SettingsSaver::getInstance().loadSettings("./Data.json");

    initPomodoroTimer();

    QObject::connect(mWndSettings, SIGNAL(newData(Data)), this, SLOT(setNewData(Data)));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete pomodoroTimer;

    delete mWndSettings;

    delete m_player;
}

void MainWindow::on_pushButton_settings_clicked()
{
    this->mWndSettings->show();
    this->mWndSettings->setData(SettingsSaver::getInstance().getData());
}

void MainWindow::on_pushButton_timeStart_clicked()
{
    this->pomodoroTimer->startPomodoroTimer();

    m_player->setMedia(QUrl(SettingsSaver::getInstance().getData().getPathToMelodyOfTick()));
    m_player->setVolume(SettingsSaver::getInstance().getData().getVolumeOfTick().toInt());
    m_player->play();
}

void MainWindow::on_pushButton_timeStop_clicked()
{
    this->pomodoroTimer->stopPomodoroTimer();

    this->ui->progressBar_work->setValue(0);

    this->ui->progressBar_break->setValue(0);

    m_player->stop();
}

void MainWindow::set_Persent_of_work(int p)
{
    this->ui->progressBar_work->setValue(p);

    if(100 == p)
    {
        m_player->stop();
        m_player->setMedia(QUrl(SettingsSaver::getInstance().getData().getPathToMelodyOfRing()));
        m_player->setVolume(SettingsSaver::getInstance().getData().getVolumeOfRing().toInt());
        m_player->play();
    }
}

void MainWindow::set_Persent_of_break(int p)
{
    this->ui->progressBar_break->setValue(p);

    if(100 == p)
    {
        m_player->stop();
        m_player->setMedia(QUrl(SettingsSaver::getInstance().getData().getPathToMelodyOfTick()));
        m_player->setVolume(SettingsSaver::getInstance().getData().getVolumeOfTick().toInt());
        m_player->play();
    }
}

void MainWindow::initPomodoroTimer()
{
    pomodoroTimer->setdurationOfWork(SettingsSaver::getInstance().getData().getDurationOfWork().toInt());
    pomodoroTimer->setdurationOfShortBreak(SettingsSaver::getInstance().getData().getDurationOfShortBreak().toInt());
    pomodoroTimer->setdurationOfLongBreak(SettingsSaver::getInstance().getData().getDurationOfLongBreak().toInt());

    QObject::connect(pomodoroTimer, SIGNAL(persentOfWork(int)), this, SLOT(set_Persent_of_work(int)));
    QObject::connect(pomodoroTimer, SIGNAL(persentOfBreak(int)), this, SLOT(set_Persent_of_break(int)));
}

void MainWindow::setNewData(Data d)
{
    SettingsSaver::getInstance().setData(d);

    SettingsSaver::getInstance().saveSettings("./Data.json");
}
