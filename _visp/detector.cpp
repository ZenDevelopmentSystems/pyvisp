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
