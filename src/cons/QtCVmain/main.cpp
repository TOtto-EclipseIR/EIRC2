#include <iostream>

#include <eirQtCV/eirQtCV.h>
#include <eirQtCV/cvMat.h>


int main(int argc, char *argv[])
{
    (void)argc;
    std::cout << "Hello " << argv[0] << " compiled " << __TIME__ << " " << __DATE__ << std::endl;
    std::cout << "OpenCV version: " << qPrintable(eirQtCV::cvVersion()) << std::endl;

    return 0;
}
