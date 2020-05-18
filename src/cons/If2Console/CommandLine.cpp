#include "CommandLine.h"


CommandLine::CommandLine(QObject *parent)
    : BaseCommandLine(parent)
{
}

void CommandLine::setup()
{
    addHelpOption();
    addVersionOption();
    addPositionalArgument(CommandLineArgument(filesDirsArgName,
        "Files-and-Dirs", "File names (wild cards allowed)"
            " and Directory Names to be used as input",
            "../input/FileName.JPG ../incoming ../nopng/*.JPG"));
    addOption(maxFileDirsOptionName(), QCommandLineOption(
                  "Maximum Pending Files and/or Directories"));

}
