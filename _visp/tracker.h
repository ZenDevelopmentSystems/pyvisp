#ifndef VISP_TRACKER_H
#define VISP_TRACKER_H

#include <iostream>
#include <boost/python.hpp>

#include <visp/vpMbEdgeKltTracker.h>

using namespace boost::python;

class VispMbObjectTracker {
  public:
    VispMbObjectTracker(const std::string &conf,
                        const std::string &model);

    void initFromPoints(const cv::Mat &img, const std::string &initPoints);

    cv::Mat track(const cv::Mat &img);

    void setPose(const cv::Mat &img, const list &pose);

    list getPose();
    list getKltPoints();

  private:
    vpMbEdgeKltTracker tracker;
    vpHomogeneousMatrix cMo;
    vpCameraParameters cam;
};

#endif // VISP_TRACKER_H
