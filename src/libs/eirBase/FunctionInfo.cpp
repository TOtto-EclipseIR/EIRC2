#include "FunctionInfo.h"

#include "Debug.h"

FunctionInfo::FunctionInfo()
{
    TRACEFN
}

FunctionInfo::FunctionInfo(const QString &qFnInfo)
    : mQFuncInfoMacro(qFnInfo)
{
    TRACEQFI << qFnInfo;
    parse();
}

void FunctionInfo::parse(const QString &qFnInfo)
{
    TRACEQFI << qFnInfo;
    mQFuncInfoMacro = qFnInfo;
    parse();
}

void FunctionInfo::parse()
{
    TRACEQFI << mQFuncInfoMacro;
    WEXPECTNOT(mQFuncInfoMacro.isEmpty())
    parseClear();
    if (mQFuncInfoMacro.isEmpty()) return;      /*<========>*/

    // Split Macro into three parts
    //  1. prior to '(' introducing parameters
    //  2. between '()' paremeters, may be empty
    //  3. After last '(' with post modifiers
    int indexOpenParenthesis = mQFuncInfoMacro.indexOf('(');
    int indexCloseParenthesis = mQFuncInfoMacro.lastIndexOf(')');
    QString preParen = mQFuncInfoMacro.left(indexOpenParenthesis);
    QString Params = mQFuncInfoMacro.mid(indexCloseParenthesis,
            indexCloseParenthesis - indexOpenParenthesis);
    QString postMods = mQFuncInfoMacro.mid(indexCloseParenthesis);

    // 1. Return Modifiers, Return Type, Namespace, ClassName, Function Name
    WANTDO(Parse #1)

    // 2. Parameters
    mParameterList.clear();
    QStringList qslParams = Params.split(',');
    int ix = 0;
    while ( ! qslParams.isEmpty())
    {
        Parameter param(qslParams.takeFirst(), ix++);
        mParameterList << param;
    }

    // 3. Member Finction Modifiers
    WANTDO(const/volatile etc)
}

void FunctionInfo::parseClear()
{
    TRACEFN
    mPreModifier.clear();
    mReturnType.clear();
    mNameSpace.clear();
    mClassName.clear();
    mFunctionName.clear();
    mParameterList.clear();
    mPostModifier.clear();
}
