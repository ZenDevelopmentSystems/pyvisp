import numpy

from _visp import VispMbObjectTracker

from .utils import Pose


class ModelBasedObjectTracker(VispMbObjectTracker):
    def __init__(self, obj_conf, obj_model, obj_init_pts):
        VispMbObjectTracker.__init__(self, obj_conf, obj_model)

        self._initialized = False
        self._init_pts = obj_init_pts

    def track(self, img):
        if not self._initialized:
            self._init_from_points(img, self._init_pts)
            self._initialized = True

        success = True
        try:
            img = VispMbObjectTracker.track(self, img)
        except RuntimeError:
            success = False

        return success, img

    @property
    def pose(self):
        return Pose(self._get_pose())
