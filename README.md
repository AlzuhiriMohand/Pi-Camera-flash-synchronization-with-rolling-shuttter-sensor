# Pi Camera flash synchronization with rolling shuttter sensor
 This repo desribes the synchronization of IMX219 with pulsed light source
 
The camera sensor is built as an array of photodetectors that are generally aligned in the shape of a rectangular or square matrix. Each photo-detector can be simulated as a bucket that is opened at the beginning of the exposure time to be filled with light photons and the number of gathered photons over a specific time (exposure time) reflects the light intensity sensed by the camera for that specific photodetector (pixel). CMOS sensors can be classified by the method of pixel reading mechanism into two types: rolling shutter and global shutter sensors. The below figure shows a rolling shutter sensor that is synchronized with a flashlight pulse. In a rolling shutter sensor, the camera cannot read all pixels at the same time and the sensor matrix is read sequentially (row by row). 


Each row starts its exposure at a different time to ensure that all the pixels have the same amount of exposure time. In other words, even if the shutter speed is increased (shorter exposure time), the speed of acquisition will be slowed by the readout speed of the sensor. The effect of this type of sensors reading method can be recognized as a spatial distortion when imaging fast-moving objects. Another downside of using this type of sensor is that different regions of the image can experience slightly different illumination in the case of using a fast-changing illumination source.
	
Global shutter sensors on the other side can stop the exposure for all pixels at the same time and then read the pixels values. As a result, global shutter sensors do not suffer from the aforementioned drawbacks of the rolling shutter sensors, but this comes with a higher fabrication cost, more complexity, slower maximum framerate, higher readout noise, and lower dynamic range. Therefore, rolling shutter sensors provide better performance for low light situations such as the environment inside a pipeline. 
	
 To overcome the rolling shutter problem, digital single-lens reflex (DSLR) cameras use mechanical shutters to stop the exposure of all pixels at the same time; therefore, high shutter speeds can be achieved even with slow reading sensors. Mechanical shutters provide a precise and robust solution for still photography with DSLR cameras, but they are not reliable for continuous video acquisition and high frame rates. Their large size also represents a problem for fitting them to small-size camera sensors. An alternative solution for dark environments is to modify the existing rolling shutter sensors to have the global shutter-like capability with careful light source synchronization. 
	
	 
In a dark environment with no access to ambient light, the only light source comes from the artificial illumination in the sensor head. This environment   reduces the interference from ambient light and provides tight control of the imaged scene illumination. In this case, we do not need to block the incoming light toward the camera sensor; instead, a light source is required to provide illumination. Therefore, the dark environment will act as a natural shutter for the camera sensor. As explained in the above figure, the frame exposure starts with a dark environment with no illumination, then a strong flash is triggered in the middle of the frame exposure for a short time followed by sensor readout (the pulse period must be smaller than the exposure to guarantee even illumination across the frame). The implementation of this solution provides the following advantages: a) Solve rolling shutter problem and thereby reduce spatial distortion, 2) Better power and thermal efficiency due to the smaller working time for the projection, and 3) Reduce motion blur due to the faster shutter speeds when the flash power is excited and concentrated in a short time frame.
	
 The embedded acquisition platform provides the ability to monitor the camera control signal. The signal is raised when the end of the first line in the frame is received from the sensor and falls when receiving the end of the last line in the frame. The exposure time starts after time T from receiving the last line of the image; i.e., the signal falling edge serves as an indicator of starting a new frame.  The delay time (T) can be calculated as follows:
	
 
 
 where fps is the frame rate and Tex is the sensor exposure time. The camera sensor is started with all initial parameters regarding the exposure time, frames per second, and digital and analog gain. An external function is created to monitor the camera signals and trigger the projector excitation. Figure a shows a flow diagram of the recording and triggering algorithm. St is a status flag with values that range from 0 to R, and R is the ratio between the number of projector and LED frames. x1 and y1 are the delay times for the projector (Proj.) and LED respectively while x2 and y2 are the exposure times for the projector and the LED respectively. Figure b shows the timing diagram of the camera acquisition signal and the projector excitation signal produced by the acquisition platform. The triggering circuit follows the falling edge from the camera and alternates between the projector and the white LED illumination. Different pulse widths were used during the experiment to provide precise control over the sensor exposure because the SL projector and the white light source have different illumination powers.
	
 
