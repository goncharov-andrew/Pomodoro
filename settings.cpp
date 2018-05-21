#include "settings.h"
#include "ui_settings.h"

#include "QDebug"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    initComboBoxes();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setData(Data const & data)
{
    mData = data;

    this->ui->horizontalSlider_volumeOfRing->setValue(mData.getVolumeOfRing().toInt());
    this->ui->horizontalSlider_volumeOfTick->setValue(mData.getVolumeOfTick().toInt());
    this->ui->lineEdit_pathToRing->setText(mData.getPathToMelodyOfRing());
    this->ui->lineEdit_pathToTick->setText(mData.getPathToMelodyOfTick());

    int index = this->ui->comboBox_longBreak->findData(mData.getDurationOfLongBreak());
    if ( index != -1 )
    {
       this->ui->comboBox_longBreak->setCurrentIndex(index);
    }

    index = this->ui->comboBox_shortBreak->findData(mData.getDurationOfShortBreak());
    if ( index != -1 )
    {
        this->ui->comboBox_shortBreak->setCurrentIndex(index);
    }

    index = this->ui->comboBox_pomodoro->findData(mData.getDurationOfWork());
    if ( index != -1 )
    {
        this->ui->comboBox_pomodoro->setCurrentIndex(index);
    }
}

void Settings::on_pushButton_openFileTick_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"", "",
                                                    tr("Settings (*.mp3);;All Files (*)"));
    if("" != fileName)
    {
        this->ui->lineEdit_pathToTick->setText(fileName);
    }
}

void Settings::on_pushButton_openFileRing_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"", "",
                                                    tr("Settings (*.mp3);;All Files (*)"));
    if("" != fileName)
    {
        this->ui->lineEdit_pathToRing->setText(fileName);
    }
}

void Settings::on_pushButton_save_clicked()
{
    mData.setDurationOfLongBreak(this->ui->comboBox_longBreak->currentText());
    mData.setDurationOfShortBreak(this->ui->comboBox_shortBreak->currentText());
    mData.setDurationOfWork(this->ui->comboBox_pomodoro->currentText());
    mData.setPathToMelodyOfRing(this->ui->lineEdit_pathToRing->text());
    mData.setPathToMelodyOfTick(this->ui->lineEdit_pathToTick->text());
    mData.setVolumeOfRing(QString::number(this->ui->horizontalSlider_volumeOfRing->value()));
    mData.setVolumeOfTick(QString::number(this->ui->horizontalSlider_volumeOfTick->value()));

    emit newData(mData);

    this->close();
}

void Settings::initComboBoxes()
{
    for(int i = MIN_SHORT_BREAK; i < MAX_SHORT_BREAK; ++i)
    {
        this->ui->comboBox_shortBreak->addItem(QString::number(i), i);
    }
    for(int i = MIN_LONG_BREAK; i < MAX_LONG_BREAK; i+=INCREMENT_OF_LONG_BREAK)
    {
        this->ui->comboBox_longBreak->addItem(QString::number(i), i);
    }
    for(int i = MIN_TIME_OF_WORK; i < MAX_TIME_OF_WORK; i+=INCREMENT_OF_LONG_POMODORO)
    {
        this->ui->comboBox_pomodoro->addItem(QString::number(i), i);
    }
}


