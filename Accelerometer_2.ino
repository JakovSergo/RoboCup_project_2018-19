#include <Wire.h>
#include <ADXL345.h>

ADXL345 acc; //variable adxl is an instance of the ADXL345 library

int ax, ay, az, prev_ax, prev_az;
unsigned long rate = 1000;
float xVelocity, prev_xVelocity, zVelocity, prev_zVelocity;
float xPosition, prev_xPosition, zPosition, prev_zPosition;

void setup(){
  Serial.begin(9600);
  acc.powerOn();
  delay(1000);
}

void loop(){
  // Acceleration on all axis
  double xyz[3];
  double ax,ay,az;
  acc.getAcceleration(xyz);
  ax = xyz[0]*9.80665; //convertion from G-force to m/s2
  ay = xyz[1]*9.80665; //convertion from G-force to m/s2
  az = xyz[2]*9.80665; //convertion from G-force to m/s2
  if (-0.30 < ax < 0.30)
    ax = 0;
  if (-0.30 < ay < 0.30)
    ay = 0;
  if (-0.30 < az < 0.30)
    az = 0;
  // Speed, distance
 /* xVelocity = prev_xVelocity + (prev_ax +(ax - prev_ax)/2)*rate;
  zVelocity = prev_zVelocity + (prev_az +(az - prev_az)/2)*rate;
  xPosition = prev_xPosition + (prev_xVelocity +(xVelocity - prev_xVelocity)/2)*rate;
  zPosition = prev_zPosition + (prev_zVelocity +(zVelocity - prev_zVelocity)/2)*rate;
  prev_ax = ax;
  prev_az = az;
  prev_xVelocity = xVelocity;
  prev_zVelocity = zVelocity;
  prev_xPosition = xPosition;
  prev_zPosition = zPosition;*/
  
  // Output
  Serial.print("X=");
  Serial.print(ax); 
    Serial.println(" m/s2");
  Serial.print("Y=");
  Serial.print(ay);
    Serial.println(" m/s2");
  Serial.print("Z=");
  Serial.print(az);
    Serial.println(" m/s2");
  Serial.println("**********************");
  delay(rate);
}
