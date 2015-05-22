import _visp

from .utils import Pose


class ModelBasedObjectTracker(_visp.MbObjectTracker):
    def track(self, img):
        success = False
        try:
            img = _visp.MbObjectTracker.track(self, img)
            success = True

        except RuntimeError:
            pass

        return success, img

    @property
    def pose(self):
        return Pose(self.get_pose())
