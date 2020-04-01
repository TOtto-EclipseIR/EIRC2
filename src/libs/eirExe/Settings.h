#pragma once

#include <QObject>


#include <eirBase/Var.h>
#include <eirBase/VarMap.h>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    Var current(const MultiName & name) const;
    Var stacked(const MultiName & name) const;

public slots:
    void set(Var var);
    void set(VarMap vars);
    void push(VarMap config);
    void pop();
    void startCommandLine();
    void finishCommandLine();


signals:
    void defaultSet(Var var);
    void overrideSet(Var var);
    void localSet(Var var);
    void pushed(Var var);
    void popped(Var var);
    void changed(Var var);

private:
    enum Source
    {
        nullSource = 0,
        Defaults,
        CommandLine,
        Local,
        Stacked,
        sizeSource
    };

private:
    Source mSource=nullSource;
    VarMap mDefaults;
    VarMap mOverrides;
    VarMap mLocals;
    VarMap::Stack mStack;
};

