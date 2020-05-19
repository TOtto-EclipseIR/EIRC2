#include "CommandLine.h"


CommandLine::CommandLine(QObject *parent)
    : BaseCommandLine(parent)
{
}

void CommandLine::setup()
{
    addPositionalArgument(filesDirsArgName,
         "File names (wild cards allowed)"
            " and Directory Names to be used as input",
            "../input/FileName.JPG ../incoming ../nopng/*.JPG");
    addOption(QCommandLineOption("MaxFilesDirs"
                  "Maximum Pending Files and/or Directories"));

}
