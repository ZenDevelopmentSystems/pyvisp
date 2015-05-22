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

void VispMbObjectTracker::initFromPose(const cv::Mat &img, const list &pose) {
  vpImage<unsigned char> I;
  vpImageConvert::convert(img, I);

  std::vector<double> v;
  for (int i=0; i < len(pose); i++) {
    v.push_back(extract<double>(pose[i]));
  }
  vpHomogeneousMatrix cMo(v);

  tracker.setPose(I, cMo);
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
