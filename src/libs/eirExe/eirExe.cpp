#include "eirExe.h"

#include "ErrorHandler.h"

eirExe::eirExe()
{
}

void eirExe::registerErrors()
{
    ErrorHandler::Item::registerCode(
                 "ErrorHandler/tryFileMode/NotExist",
                 QtCriticalMsg,
                 "%What %FileName at %FilePath does not exist",
                 VarMap() << Var("What", "File's purpose")
                     << Var("FileName", "File's Name")
                     << Var("FilePath", "File's Directory"));
    ErrorHandler::Item::registerCode(
                 "ErrorHandler/tryFileMode/NotReadable",
                 QtCriticalMsg,
                 "%What %FileName at %FilePath is not readable",
                 VarMap() << Var("What", "File's purpose")
                     << Var("FileName", "File's Name")
                     << Var("FilePath", "File's Directory"));
    ErrorHandler::Item::registerCode(
                 "ErrorHandler/tryFileMode/NotWritable",
                 QtCriticalMsg,
                 "%What %FileName at %FilePath is not writable",
                 VarMap() << Var("What", "File's purpose")
                     << Var("FileName", "File's Name")
                     << Var("FilePath", "File's Directory"));
}
