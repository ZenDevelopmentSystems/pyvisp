#ifndef VISP_BOOST_CONVERTER_H
#define VISP_BOOST_CONVERTER_H

#include <vector>
#include <opencv2/core.hpp>
#include <boost/python.hpp>

#include <visp/vpHomogeneousMatrix.h>
#include <visp/vpImage.h>
#include <visp/vpRect.h>

using namespace boost::python;

class VISPConverter {
  public:
    static cv::Mat fromVpImage(const vpImage<unsigned char> &I);
    static cv::Mat fromVpImage(const vpImage<vpRGBa> &I);

    static list convertToBoost(const vpImagePoint &from);
    static list convertToBoost(const vpRect &from);
    static list convertToBoost(const vpHomogeneousMatrix &cMo);

    static list convertToBoost(const std::vector<vpImagePoint> &from);
};

#endif
