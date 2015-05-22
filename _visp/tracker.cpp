#include <png.h>

#include "tracker.h"

#include "VISPBoostConverter.h"
#include "dummyDisplayOpenCV.h"


VispMbObjectTracker::VispMbObjectTracker(const std::string &conf,
                                         const std::string &model) {
  tracker.loadConfigFile(conf);
  tracker.getCameraParameters(cam);

  tracker.loadModel(model);
  tracker.setDisplayFeatures(true);
}


void VispMbObjectTracker::initFromPoints(const cv::Mat &img,
                                         const std::string &initPoints) {
  vpImage<unsigned char> I;
  vpImageConvert::convert(img, I);

  tracker.initFromPoints(I, initPoints);
}

cv::Mat VispMbObjectTracker::track(const cv::Mat &img) {
  vpImage<unsigned char> I;
  vpImageConvert::convert(img, I);

  tracker.track(I);

  tracker.getPose(cMo);
  tracker.getCameraParameters(cam);

  DummyDisplayOpenCV tmp;

  tmp.init(I);
  tmp.display(I);
  tracker.display(I, cMo, cam, vpColor::red, 2, true);

  vpImage<vpRGBa> dst;
  tmp.getImage(dst);

  return VISPConverter::fromVpImage(dst);
}

list VispMbObjectTracker::getPose() {
  return VISPConverter::convertToBoost(cMo);
}
