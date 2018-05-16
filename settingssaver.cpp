#include "settingssaver.h"
#include <QTextCodec>

QString SettingsSaver::parseDataToJSON()
{
    QJsonObject jsonObj;
    jsonObj["VolumeOfRing"] = mData.getVolumeOfRing();
    jsonObj["VolumeOfTick"] = mData.getVolumeOfTick();
    jsonObj["PathToMelodyOfRing"] = mData.getPathToMelodyOfRing();
    jsonObj["PathToMelodyOfTick"] = mData.getPathToMelodyOfTick();
    jsonObj["DurationOfShortBreak"] = mData.getDurationOfShortBreak();
    jsonObj["DurationOfLongBreak"] = mData.getDurationOfLongBreak();
    jsonObj["DurationOfWork"] = mData.getDurationOfWork();

    QJsonDocument doc(jsonObj);

    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QString result = codec->toUnicode((doc.toJson(QJsonDocument::Indented)));

    return result;
}

void SettingsSaver::parseDataFromJSON(QString const & data)
{
    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());

    QJsonObject jsonObj = document.object();
    mData.setVolumeOfRing(jsonObj["VolumeOfRing"].toString());
    mData.setVolumeOfTick(jsonObj["VolumeOfTick"].toString());
    mData.setPathToMelodyOfRing(jsonObj["PathToMelodyOfRing"].toString());
    mData.setPathToMelodyOfTick(jsonObj["PathToMelodyOfTick"].toString());
    mData.setDurationOfShortBreak(jsonObj["DurationOfShortBreak"].toString());
    mData.setDurationOfLongBreak(jsonObj["DurationOfLongBreak"].toString());
    mData.setDurationOfWork(jsonObj["DurationOfWork"].toString());
}

void SettingsSaver::loadSettings(QString const & pathToLoad)
{
    QString result = "";

    QFile file;
    file.setFileName(pathToLoad);
    if (file.open(QIODevice::ReadOnly))
    {
        while (!file.atEnd())
        {
            result += file.readLine();
        }
    }

    parseDataFromJSON(result);
}

void SettingsSaver::saveSettings(QString const & pathToSave)
{
    QString result = parseDataToJSON();

    QFile file;
    file.setFileName(pathToSave);

    if(0 != file.exists())
    {
        file.remove();
    }

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream out(&file);

        out << result;
    }
    file.close();
}

void SettingsSaver::setData(Data d)
{
    this->mData = d;
}

Data const & SettingsSaver::getData()
{
    return this->mData;
}

Data::Data()
{
    mVolumeOfRing = "";
    mVolumeOfTick = "";
    mPathToMelodyOfRing = "";
    mPathToMelodyOfTick = "";
    mDurationOfShortBreak = "";
    mDurationOfLongBreak = "";
    mDurationOfWork = "";
}

Data::Data(Data const & data)
{
    this->mVolumeOfRing = data.mVolumeOfRing;
    this->mVolumeOfTick = data.mVolumeOfTick;
    this->mPathToMelodyOfRing = data.mPathToMelodyOfRing;
    this->mPathToMelodyOfTick = data.mPathToMelodyOfTick;
    this->mDurationOfShortBreak = data.mDurationOfShortBreak;
    this->mDurationOfLongBreak = data.mDurationOfLongBreak;
    this->mDurationOfWork = data.mDurationOfWork;
}

Data & Data::operator=(Data const & data)
{
    if(this != &data)
    {
        this->mVolumeOfRing = data.mVolumeOfRing;
        this->mVolumeOfTick = data.mVolumeOfTick;
        this->mPathToMelodyOfRing = data.mPathToMelodyOfRing;
        this->mPathToMelodyOfTick = data.mPathToMelodyOfTick;
        this->mDurationOfShortBreak = data.mDurationOfShortBreak;
        this->mDurationOfLongBreak = data.mDurationOfLongBreak;
        this->mDurationOfWork = data.mDurationOfWork;
    }

    return *this;
}

QString const & Data::getVolumeOfRing() const
{
    return this->mVolumeOfRing;
}

QString const & Data::getVolumeOfTick() const
{
    return this->mVolumeOfTick;
}

QString const & Data::getPathToMelodyOfRing() const
{
    return this->mPathToMelodyOfRing;
}

QString const & Data::getPathToMelodyOfTick() const
{
    return this->mPathToMelodyOfTick;
}

QString const & Data::getDurationOfShortBreak() const
{
    return this->mDurationOfShortBreak;
}

QString const & Data::getDurationOfLongBreak() const
{
    return this->mDurationOfLongBreak;
}

QString const & Data::getDurationOfWork() const
{
    return this->mDurationOfWork;
}

void Data::setVolumeOfRing(QString const & data)
{
    this->mVolumeOfRing = data;
}

void Data::setVolumeOfTick(QString const & data)
{
    this->mVolumeOfTick = data;
}

void Data::setPathToMelodyOfRing(QString const & data)
{
    this->mPathToMelodyOfRing = data;
}

void Data::setPathToMelodyOfTick(QString const & data)
{
    this->mPathToMelodyOfTick = data;
}

void Data::setDurationOfShortBreak(QString const & data)
{
    this->mDurationOfShortBreak = data;
}

void Data::setDurationOfLongBreak(QString const & data)
{
    this->mDurationOfLongBreak = data;
}

void Data::setDurationOfWork(QString const & data)
{
    this->mDurationOfWork = data;
}
