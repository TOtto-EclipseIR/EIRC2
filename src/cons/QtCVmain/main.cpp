#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <eirCascade/CascadeType.h>
#include <eirQtCV/eirQtCV.h>
#include <eirQtCV/cvCascade.h>
#include <eirQtCV/cvMat.h>

cvCascade gPreScanCascade;

int main(int argc, char *argv[])
{
    (void)argc;

    std::cout << "Hello " << argv[0] << " compiled " << __TIME__ << " " << __DATE__ << std::endl;
    std::cout << "OpenCV version: " << qPrintable(eirQtCV::cvVersion()) << std::endl;

    if ( ! gPreScanCascade.loadCascade(QFileInfo(("D:/bin/detectors/v4/haarcascade_frontalcatface_extended.Xml"))))
    {
        std::cerr << "gPreScanCascade.loadCascade() failed" << std::endl;
        return 1;
    }
    std::cout << "Cascade: " << qPrintable(gPreScanCascade.cascadeFileInfo().filePath())
              << (gPreScanCascade.isLoaded() ? " loaded" : " IS NOT LOADED") << std::endl;

    cvMat inputQMat;
    inputQMat.imread("D:/INDIface/INDIin/console/hide/18yoTwins.jpg", cv::IMREAD_COLOR);
    cv::imshow("inputQMat", inputQMat.mat());
    std::cout << qPrintable(inputQMat.dumpString()) << std::endl;
    cv::waitKey();
    std::cout << qPrintable(inputQMat.dumpString()) << std::endl;

    cvMat detectQMat(inputQMat.rows(), inputQMat.cols(), CV_8UC1);
    inputQMat.makeGrey(detectQMat);
    std::cout << qPrintable(detectQMat.dumpString()) << std::endl;
    cv::imshow("detectQMat", detectQMat.mat());
    cv::waitKey();



    return 0;
}
