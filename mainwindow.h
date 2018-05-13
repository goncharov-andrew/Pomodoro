#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "settings.h"
#include "settingssaver.h"
#include "pomodorotimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_settings_clicked();

    void on_pushButton_timeStart_clicked();

    void on_pushButton_timeStop_clicked();

    void set_Persent_of_work(int p);

    void set_Persent_of_break(int p);

    void initPomodoroTimer();

    void setNewData(Data d);

private:
    Ui::MainWindow *ui;
    PomodoroTimer *pomodoroTimer;
    Settings *mWndSettings;
    QMediaPlayer *m_player;
};

#endif // MAINWINDOW_H
