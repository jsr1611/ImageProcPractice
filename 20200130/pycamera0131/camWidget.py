
from picamera.array import PiRGBArray
from picamera import PiCamera
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import time
import cv2

class VideoWindow(QWidget):
	def __init__(self):
		QWidget.__init__(self)
		recording = 0
		
		vbl = QVBoxLayout()
		photo = QPushButton("save jpg")
		
		self.myLabel = QLabel()
		
		vbl.addWidget(photo)
		vbl.addWidget(self.myLabel)
		self.setLayout(vbl)
		
		self.camera = PiCamera()
		self.camera.resolution = (640, 480)
		self.camera.framerate = 32
		self.rawCapture = PiRGBArray(self.camera, size=(640,480))
		time.sleep(0.1)
		self.frame = iter(self.camera.capture_continuous(self.rawCapture, format="rgb", use_video_port=True))
		
		QObject.connect(photo, SIGNAL("clicked()"), self.takePicture)
		
		self.timer = QTimer()
		QObject.connect(self.timer, SIGNAL("timeout()"),self.updatePicture)
		self.timer.start(10)
		
	def releaseCamera(self):
		self.camera.close()
	def updatePicture(self):
		dataArray = next(self.frame).array
		
		qImg = QImage(dataArray, 640, 480, QImage.Format_RGB888)
		
		self.myLabel,resize(640,480)
		self.myLabel.setPixmap(QPixmap,fromImage(qImg))
		self.myLabel.show()
		
		self.rawCapture.truncate(0)
		
	def takePicture(self):
		self.camera.capture('picture.jpg')
		print("picture saved")
					
app = QApplication([])
	
w = VideoWindow()
w.show()
	
app.exec_()
	
w.releaseCamera()
