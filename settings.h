#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QFileDialog>
#include "settingssaver.h"
#include "constants.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void setData(Data const & data);

private slots:

    void on_pushButton_save_clicked();

    void on_pushButton_openFileTick_clicked();

    void on_pushButton_openFileRing_clicked();

signals:

    void newData(Data d);

private:
    Ui::Settings *ui;

    Data mData;

    void initComboBoxes();
};

#endif // SETTINGS_H
