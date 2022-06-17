# Pi Camera flash synchronization with rolling shuttter sensor
 This small repo desribes the synchronization of two IMX219 sensors working as stereo camera with two pulsed light sources (white and structured light but it could be any types of light). This code is intended for special case use where the cameras are working in a dark environement.
 
 The code was implemented to provide  1) Allow synchronized acquisition by alternating between the SL and white LED, 2) Solve rolling shutter problem and thereby reduce spatial distortion during the sensor movement, 3) Better power and thermal efficiency due to the smaller working time for the projection, and 4) Reduce motion blur due to the faster shutter speeds when the flash power is excited and concentrated in a short time, and finaly 5) Very tight stereo synchronization.
 
This code was inspired by the work done by Hermann-SW on simulated global in Pi cameras. You can check his work and the modifications required for the pi registery  from the following link: https://github.com/Hermann-SW/Raspberry_v1_camera_global_external_shutter

If you are interested in a scientific explanation of the process, you can check section 4.2 of my thesis (don't hesitate to shoot me a message if you found any errors or mistakes in the thesis report). A compressed version of the thesis is available from the following link: https://github.com/AlzuhiriMohand/AlzuhiriMohand/blob/main/Multi-Modality_Nondestructive__compressed.pdf

Code Excecution
 
1) Run the flash triggering routine\
	sudo ./SynchedFlash 2000 1000 15\
2000 is source1 exposure, 1000 is source2 exposure and 15 is the framee rate of the camera

2) Run the camera script\
sudo ./raspivid_Frex

Enjoy :smiley:

To cite this work; use the following bibliography:

@phdthesis{alzuhiri2022multi,
  title={Multi-Modality Nondestructive Evaluation Techniques for Inspection of Plastic and Composite Pipeline Networks},
  author={Alzuhiri, Mohand},
  year={2022},
  school={Michigan State University}
}




