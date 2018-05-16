#ifndef SETTINGSSAVER_H
#define SETTINGSSAVER_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>

class Data
{
private:
    QString mVolumeOfRing;
    QString mVolumeOfTick;
    QString mPathToMelodyOfRing;
    QString mPathToMelodyOfTick;
    QString mDurationOfShortBreak;
    QString mDurationOfLongBreak;
    QString mDurationOfWork;

public:
    explicit Data();
    Data(Data const &);
    Data & operator=(Data const &);

    QString const & getVolumeOfRing() const;
    QString const & getVolumeOfTick() const;
    QString const & getPathToMelodyOfRing() const;
    QString const & getPathToMelodyOfTick() const;
    QString const & getDurationOfShortBreak() const;
    QString const & getDurationOfLongBreak() const;
    QString const & getDurationOfWork() const;

    void setVolumeOfRing(QString const & data);
    void setVolumeOfTick(QString const & data);
    void setPathToMelodyOfRing(QString const & data);
    void setPathToMelodyOfTick(QString const & data);
    void setDurationOfShortBreak(QString const & data);
    void setDurationOfLongBreak(QString const & data);
    void setDurationOfWork(QString const & data);
};

class SettingsSaver
{
public:
    static SettingsSaver & getInstance()
    {
        static SettingsSaver setServer;
        return setServer;
    }
    void loadSettings(QString const & pathToLoad);
    void saveSettings(QString const & pathToSave);
    void setData(Data d);
    Data const & getData();

private:
    SettingsSaver(){}
    SettingsSaver(SettingsSaver const &);
    SettingsSaver &operator=(SettingsSaver const &);
    QString parseDataToJSON();
    void parseDataFromJSON(QString const & data);
    Data mData;
};

#endif // SETTINGSSAVER_H
