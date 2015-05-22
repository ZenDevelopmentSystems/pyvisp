import time
import cv2

from numpy import array, mean, std

from visp.tracker import ModelBasedObjectTracker

res = 640, 480

if __name__ == '__main__':
    cap = cv2.VideoCapture('teabox-demo-2.mov')

    tracker = ModelBasedObjectTracker('teabox.xml', 'teabox.cao')
    tracker.init_from_points(cv2.imread('teabox.png'), 'teabox.init')

    dt = []

    while True:
        success, img = cap.read()
        if not success:
            break

        start = time.time()
        success, img = tracker.track(img)
        end = time.time()

        print(tracker.pose.translation_vector)

        dt.append(end - start)
        if len(dt) == 20:
            dt = array(dt) * 1000
            print('Average tracking time {}ms (STD={})'.format(mean(dt), std(dt)))
            dt = []

        cv2.imshow('Live Video', img)
        cv2.waitKey(1)
