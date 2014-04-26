/*
	Written by Tihomir Nedev (mail@tnedev.com)
	April 2014
	V 1.0
	Function measuring the db noise level with the 1133_0 Phidgets Sound Sensor
	Available at: http://www.active-robots.com/shop-by-brand/phidgets/sensors/light-sound/sound-sensor.html	
	
*/

#include <math.h>

byte mic_pin = A0; // Sound sensor's signal to pin A0
byte sensitivity = 9; // |From 0 to 10 | Set the sensitivity of the sensor. 10 is the highest sensitivity.

void setup() {
	Serial.begin(9600);
}

void loop() {

  
 
	Serial.println(measure_noise(),4); // Print the db level on the screen
}

double measure_noise()
{
	double analog_step=0.00488; // Voltage step for the ADC. 5 volts / 1024 steps
	int raw ;                   // value to store raw adc input
	double rms=0.0;				// value to store the RMS value for the readings
	double vin_value = 0.0;		// Value to store the voltage input from the microphone. It is the raw converted to voltage
	double output = 0.0 ;		// output in db
	double addition = 0.0;		// value to store addition for the rms
	double matrix[100];			// array to store the elemets for the rms

	for (int i=0;i<100;i++)   // Take 100 readings to calculate RMS value
	{
		raw = analogRead(mic_pin); // Read the sensor
		vin_value = (raw*analog_step); // Convert ADC signal to voltage
		matrix[i]=vin_value;			// Assign the voltage to the matrix
		matrix[i]=matrix[i]*matrix[i];	// Calculate the square of the value. Pre RMS calculation
		addition += matrix[i]; 			// Add all squares to this variable
		delay((10-sensitivity));
	}	
	addition = addition/100.0; // Take the avarage
	rms = sqrt(addition);      // Take the squate root
	output = (168.01 * log(rms*200)/10)+9.87; // Formula for the db level according to the documentation of the sound sensor
	
	return output; // return the value

}
