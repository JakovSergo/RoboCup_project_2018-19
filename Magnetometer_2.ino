#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified();  // sets the magnetometer on Adarfuit board
float xNorth, yNorth;
float newAngle = 0;
float initialAngle;
float declination = 0.0698; //angle describing the error between magnetic and real north

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Starting HMC test...");
  Serial.println(" ");
  if(!mag.begin())
    Serial.println("Sensor not found");
  delay(500);
  
  // Location of initial angle between north and real direction
  Serial.println("Locating...");
  sensors_event_t north;  // sensor event - location of north
  mag.getEvent(&north);   // gets magnetometer's data on all 3 axis
  xNorth = north.magnetic.x;   // milliGauss on the x axis
  yNorth = north.magnetic.y;   // milliGauss on the y axis
  initialAngle = atan2(xNorth, yNorth);   // finding the starting angle (azimuth)
  initialAngle += declination;  // taking into account the declination angle in Zagreb
  Serial.print("Initial angle:");
  Serial.println(initialAngle*180/M_PI);  // converts the result to degrees
  delay(1000);
}

void loop() {
  sensors_event_t data;   // sensor event - evaluating data
  mag.getEvent(&data);
  float heading = atan2(data.magnetic.x, data.magnetic.y);  // again finds the azimuth
  heading += declination;
  newAngle = heading - initialAngle;  // the result - angle between the desired "north" and current direction
 /* if(newAngle < 0) //correction for reverse signs
    newAngle += 2*PI; 
  if(newAngle > 2*PI)
    newAngle -= 2*PI;*/
  Serial.print("Heading: ");
  Serial.println(newAngle*180/M_PI);
  delay(1000);
}
