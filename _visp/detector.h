#ifndef VISP_DETECTOR_H
#define VISP_DETECTOR_H

#include <boost/python.hpp>
#include <opencv2/core/core.hpp>

#include <visp/vpDetectorQRCode.h>

using namespace cv;
using namespace boost::python;

struct QRCode {
    list polygon;
    std::string message;
    list cog;
    list bounding_box;
};

class VispQRCodeDetector {
  public:
    VispQRCodeDetector();

    list detect(const cv::Mat &img);

private:
  vpDetectorQRCode detector;
};

#endif // VISP_DETECTOR_H
