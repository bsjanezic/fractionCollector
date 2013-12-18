
To use this sketch:
 - if your computer does not already have the latest version of the Arduino IDE, download it here:  http://arduino.cc/en/Main/Software
 - install the adafruit_MotorShield library and RTClib files by placing them in the libraries folder in the arduino application
- open the sketch titled twoAxisSampler

- to change the time interval between samples, change this line:

		int timeInterval = 35;
to the time interval in minutes you’d like between samples. 

- if sampling less than 48 bottles, change this line:
	int sampleCount = 48;
to the correct sample count. cannot exceed 49.
