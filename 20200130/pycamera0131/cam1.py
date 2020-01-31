
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

# calling camera info
camera = PiCamera()
rawCapture = PiRGBArray(camera)

# camera warm up time add
time.sleep(0.1)

while True:
	# capture image using camera 
	camera.capture(rawCapture, format="bgr")
	image = rawCapture.array
	
	# show image on display
	cv2.imshow("image", image)
	key = cv2.waitKey(1) & 0xff
	if key == 27:
		break
		
