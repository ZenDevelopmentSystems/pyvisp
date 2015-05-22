import cv2
import numpy

import _visp


class QRCodeDetector(_visp.QRCodeDetector):
    def detect(self, img):
        return [QRCode(c) for c in _visp.QRCodeDetector.detect(self, img)]


class QRCode(object):
    def __init__(self, code):
        self._code = code

    def draw(self, img):
        cv2.polylines(img, numpy.array([self.polygon], dtype=numpy.int32),
                      True, (0, 0, 255), 2)

        cv2.putText(img, self.message, self.center,
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    @property
    def message(self):
        return self._code.message

    @property
    def center(self):
        return tuple(map(int, self._code.cog))

    @property
    def bounding_box(self):
        return numpy.array(self._code.bounding_box)

    @property
    def polygon(self):
        return numpy.array(self._code.polygon)
