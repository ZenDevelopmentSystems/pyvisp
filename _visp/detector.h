#ifndef VISP_DETECTOR_H
#define VISP_DETECTOR_H

#include <boost/python.hpp>
#include <opencv2/core/core.hpp>

#include <visp/vpDetectorQRCode.h>
#include <visp/vpMbEdgeTracker.h>
#include <visp/vpKeyPoint.h>

#include "tracker.h"

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

class VispObjectKeypointDetector {
public:
  VispObjectKeypointDetector(const std::string &detector);

  void loadLearningData(const std::string &filename);

  bool trainAndSave(VispMbObjectTracker &tracker,
                    const cv::Mat &img,
                    const std::string &filename);

  list detect(const cv::Mat &img);

private:
  vpKeyPoint keypoint_learning;
  vpCameraParameters cam;
};

#endif // VISP_DETECTOR_H
