#include <png.h>

#include "VISPBoostConverter.h"

#include <visp/vpConvert.h>
#include <visp/vpImageConvert.h>

template<class T>
list std_vector_to_py_list(const std::vector<T>& v)
{
    object get_iter = iterator<std::vector<T> >();
    object iter = get_iter(v);
    list l(iter);
    return l;
}

template<class T>
list visp_vector_to_py_list(const std::vector<T> &v)
{
  list l;

  for (uint i=0; i < v.size(); i++) {
    l.append(VISPConverter::convertToBoost(v[i]));
  }

  return l;
}

cv::Mat VISPConverter::fromVpImage(const vpImage<unsigned char> &I) {
  cv::Mat img;
  vpImageConvert::convert(I, img);
  return img;
}

cv::Mat VISPConverter::fromVpImage(const vpImage<vpRGBa> &I) {
  cv::Mat img;
  vpImageConvert::convert(I, img);
  return img;
}

list VISPConverter::convertToBoost(const vpImagePoint &from) {
  cv::Point2f to;
  vpConvert::convertToOpenCV(from, to);

  list l;
  l.append(to.x);
  l.append(to.y);
  return l;
}

list VISPConverter::convertToBoost(const vpRect &from) {
  list l;

  l.append(from.getTop());
  l.append(from.getLeft());
  l.append(from.getWidth());
  l.append(from.getHeight());

  return l;
}

list VISPConverter::convertToBoost(const vpHomogeneousMatrix &cMo) {
  vpHomogeneousMatrix mine(cMo);

  std::vector<double> v;
  mine.convert(v);

  return std_vector_to_py_list(v);
}

list VISPConverter::convertToBoost(const std::vector<vpImagePoint> &from) {
  return visp_vector_to_py_list(from);
}
