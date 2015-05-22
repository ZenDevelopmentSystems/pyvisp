import cv2

from visp.detector import ObjectKeypointDetector
from visp.tracker import ModelBasedObjectTracker

if __name__ == '__main__':
    detector = ObjectKeypointDetector(detector='detection-config.xml')

    img = cv2.imread('teabox.png')

    assert not detector.detect(img)

    tracker = ModelBasedObjectTracker('teabox.xml', 'teabox.cao')
    tracker.init_from_points(img, 'teabox.init')

    detector.train_and_save(tracker, img, 'teabox_learning.data')
    print(detector.detect(img))

    # Now, we reload pre-trained data
    pretrained_detector = ObjectKeypointDetector(detector='detection-config.xml',
                                                 learning_data='teabox_learning.data')
    print(detector.detect(img))
