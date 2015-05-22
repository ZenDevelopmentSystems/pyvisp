import numpy


class Pose(object):
    def __init__(self, data):
        self._pose = numpy.array(data).reshape(3, 4)

    def __repr__(self):
        return repr(self._pose)

    @property
    def pose(self):
        return self._pose

    @property
    def translation_vector(self):
        return self.pose[:, 3]

    @property
    def rotation_matrix(self):
        return self.pose[:3, :3]
