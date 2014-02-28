#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <QDebug>

class Settings
{

private:
    QSettings* _set;

public:
    explicit Settings(QString filename)
    {
        QString adr = QApplication::applicationDirPath() + "/../config/" + filename;
        _set = new QSettings(adr, QSettings::IniFormat);
        qDebug() << "Config file:  " << adr;
        if(_set->status()!=QSettings::NoError)
            qDebug() << "Loading Setting file FAILED !!!" << endl;
    }

    QString Get(QString group, QString key)
    {
        _set->beginGroup(group);
        QString ans = _set->value(key).toString();
        _set->endGroup();
        return ans;
    }

    void SetValue(QString group, QString key, QString value)
    {
        _set->beginGroup(group);
        _set->setValue(key, value);
        _set->endGroup();
    }
};

#endif // SETTINGS_H
