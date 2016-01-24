/* HMC5883 magnentometer heading code
   Adapted by Lukas Lazarek from example code in Adafruit_HMC5883_U library written by Kevin Townsend.

   Libraries required: Adafruit_Sensor, Adafruit_HMC5883_U; obtained from
   https://learn.adafruit.com/adafruit-hmc5883l-breakout-triple-axis-magnetometer-compass-sensor/wiring-and-test
   along with wiring instructions.
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial.begin(9600);
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    Serial.println("Error initializing HMC5883");
    while(1);
  }
  
  /* Display information about the HMC5883 */
  displaySensorDetails();
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  /*Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");*/

  // Sensor is held sideways (with Y being the vertical axis), so heading is calculated using X and Z
  float heading = atan2(event.magnetic.z, event.magnetic.x);
  
  // Need to account of error based upon location, find declination angle for location at http://www.magnetic-declination.com/
  float declinationAngle = 0.244346; // radians
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 

  // Print heading in terms of N/S/E/W
  if(headingDegrees >= 338 || headingDegrees < 4) Serial.println("SE");
  else if(headingDegrees >= 4 && headingDegrees < 31.75) Serial.println("E");
  else if(headingDegrees >= 31.75 && headingDegrees < 61.25) Serial.println("NE");
  else if(headingDegrees >= 61.25 && headingDegrees < 97) Serial.println("N");
  else if(headingDegrees >= 97 && headingDegrees < 139) Serial.println("NW");
  else if(headingDegrees >= 139 && headingDegrees < 201.25) Serial.println("W");
  else if(headingDegrees >= 201.25 && headingDegrees < 283.75) Serial.println("SW");
  else if(headingDegrees >= 283.75 && headingDegrees < 338) Serial.println("S");
  
  delay(250);
}
