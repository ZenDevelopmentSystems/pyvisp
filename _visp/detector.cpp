#include <png.h>

#include "detector.h"

#include <visp/vpImageConvert.h>

#include "VISPBoostConverter.h"


VispQRCodeDetector::VispQRCodeDetector() {
}

list VispQRCodeDetector::detect(const cv::Mat &img) {
  vpImage<unsigned char> I;
  vpImageConvert::convert(img, I);

  list qrCodes;

  if (detector.detect(I)) {
    for (uint i=0; i < detector.getNbObjects(); i++) {

      QRCode code;
      code.polygon = VISPConverter::convertToBoost(detector.getPolygon(i));
      code.message = detector.getMessage(i);
      code.bounding_box = VISPConverter::convertToBoost(detector.getBBox(i));
      code.cog = VISPConverter::convertToBoost(detector.getCog(i));

      qrCodes.append(code);
    }
  }

  return qrCodes;
}

VispObjectKeypointDetector::VispObjectKeypointDetector(const std::string &detector) {
  keypoint_learning.loadConfigFile(detector);
}

void VispObjectKeypointDetector::loadLearningData(const std::string &filename) {
  keypoint_learning.loadLearningData(filename, true);
}

bool VispObjectKeypointDetector::trainAndSave(VispMbObjectTracker &tracker,
                                              const cv::Mat &img,
                                              const std::string &filename) {
  vpImage<unsigned char> I;
  vpImageConvert::convert(img, I);

  vpCameraParameters cam = tracker.cam;
  tracker.tracker.track(I);

  std::vector<cv::KeyPoint> trainKeyPoints;
  double elapsedTime;
  keypoint_learning.detect(I, trainKeyPoints, elapsedTime);

  std::vector<vpPolygon> polygons;
  std::vector<std::vector<vpPoint> > roisPt;
  std::pair<std::vector<vpPolygon>, std::vector<std::vector<vpPoint> > > pair = tracker.tracker.getPolygonFaces(false);
  polygons = pair.first;
  roisPt = pair.second;

  std::vector<cv::Point3f> points3f;

  vpHomogeneousMatrix cMo = tracker.cMo;
  vpKeyPoint::compute3DForPointsInPolygons(cMo, cam, trainKeyPoints, polygons, roisPt, points3f);
  keypoint_learning.buildReference(I, trainKeyPoints, points3f);
  keypoint_learning.saveLearningData(filename, true);  

  return true;
}

list VispObjectKeypointDetector::detect(const cv::Mat &img) {
  vpImage<unsigned char> I;
  vpImageConvert::convert(img, I);

  double error;
  double elapsedTime;

  vpHomogeneousMatrix cMo;
  if (keypoint_learning.matchPoint(I, cam, cMo, error, elapsedTime)) {
    return VISPConverter::convertToBoost(cMo);
  }
  return list();
}
