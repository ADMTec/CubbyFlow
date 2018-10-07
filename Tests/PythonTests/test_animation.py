import pyCubbyFlow

class MyAnimation(pyjet.Animation):
    def __init__(self):
        self.lastFrame = None
        super(MyAnimation, self).__init__()

    def onUpdate(self, frame):
        self.lastFrame = frame

def test_inheritance():
    anim = MyAnimation()
    f = pyCubbyFlow.Frame(3, 0.02)
    anim.update(f)
    assert anim.lastFrame.index == 3
    assert anim.lastFrame.timeIntervalInSeconds == 0.02
