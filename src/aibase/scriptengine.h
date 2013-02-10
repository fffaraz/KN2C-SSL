#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QObject>
#include <QtCore>
#include <QtScript>
#include <QScriptClass>
#include <QScriptValue>
#include <QtScriptTools>
#include <QDebug>
#include "soccer.h"

class Soccer;

class ScriptEngine : public QObject
{
    Q_OBJECT

public:
    explicit ScriptEngine(QObject *parent = 0);
    QScriptValue evalFile(QString file);
    QScriptValue evalString(QString script);
    void AddObject(QObject* qobj, QString name);

private:
    QScriptEngine _engine;
    QScriptEngineDebugger _debugger;

signals:

public slots:

};

#endif // SCRIPTENGINE_H
