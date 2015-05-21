import time
import cv2

from numpy import array, mean, std

from visp.detector import QRCodeDetector

res = 640, 480

if __name__ == '__main__':
    cap = cv2.VideoCapture(0)

    cap.set(cv2.CAP_PROP_FRAME_WIDTH, res[0])
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, res[1])

    qr_code_detector = QRCodeDetector()

    dt = []

    while True:
        success, img = cap.read()

        start = time.time()
        qr_codes = qr_code_detector.detect(img)
        end = time.time()

        for code in qr_codes:
            code.draw(img)

        dt.append(end - start)
        if len(dt) == 20:
            dt = array(dt) * 1000
            print('Average detection time {}ms (STD={})'.format(mean(dt), std(dt)))
            dt = []

        cv2.imshow('Live Video', img)
        cv2.waitKey(20)
