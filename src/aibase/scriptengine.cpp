#include "scriptengine.h"

ScriptEngine::ScriptEngine(QObject *parent) :
    QObject(parent),
    _engine(this),
    _debugger(this)
{
    qDebug() << "ScriptEngine Initialization...";
    _debugger.attachTo(&_engine);
    _debugger.action(QScriptEngineDebugger::QScriptEngineDebugger::GoToLineAction);
    //_debugger.standardWindow()->show();
}

QScriptValue ScriptEngine::evalFile(QString file)
{
    QFile scriptfile(QApplication::applicationDirPath() + "/../script/" + file);
    scriptfile.open(QIODevice::ReadOnly);
    return _engine.evaluate(scriptfile.readAll(), file);
}

QScriptValue ScriptEngine::evalString(QString text)
{
    return _engine.evaluate(text);
}

void ScriptEngine::AddObject(QObject *qobj, QString name)
{
    //QScriptValue sobj=_engine.newQObject(qobj);
    //_engine.globalObject().setProperty(name, sobj);
}
