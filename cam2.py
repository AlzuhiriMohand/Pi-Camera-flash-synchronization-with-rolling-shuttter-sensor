import picamera
import time
camera = picamera.PiCamera(stereo_mode='top-bottom', resolution=(1664,1232*2),camera_num=1)

#camera = picamera.PiCamera(stereo_mode='side-by-side', resolution=(3296,1232),camera_num=0)
#camera.sensor_mode=4
camera.framerate=3.7
camera.shutter_speed=50000
camera.iso=100
camera.start_preview(fullscreen=False ,window=(1000,300,640,480*2))

#camera.exposure_mode='night'
#camera.iso=400
camera.awb_mode = 'off'
camera.awb_gains = (1.3671875,1.859375)
#camera.exposure_mode='off'
#
#camera.start_preview(fullscreen=False,window=(10,500,480,270), window= right)
print('Enter to start recording')
x = input()

camera.start_recording('/media/pi/picoS/calCam9.data', format='yuv')
print('Enter to end recording')
x = input()

camera.stop_preview()
camera.close()
#camera.exposure_mode='off'
#camera.exposure_mode='night'

#camera.exposure_mode='off'
#camera=picamera.PiCamera(camera_num=0)
'''
camera.start_recording('/media/pi/picoS/calCam0.data', format='yuv')
camera.wait_recording(60)
camera.stop_recording()
camera.close()



##camera.stop_preview()
#exit(0)
camera.stop_preview()
#camera.close()
'''
