#define GPSSerial Serial1
#define GPSECHO true

#include <CrsfSerial.h>
#include <Servo.h>
#include <ServoStabilizer.h>
#include <MPU6050.h>
#include <BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GPS.h>
#include <Adafruit_HMC5883_U.h>

SerialPIO Receiver(10, 11); //Tx, Rx
CrsfSerial crsf(Receiver, 200000);

Servo Aileron, Elevator, Motor, Rudder;

SerialPIO reyax(12,13); //TX, RX
String reyaxReceived[8];

int counter=0;
uint32_t timer1 = millis();
uint32_t timer2 = millis();
Adafruit_GPS GPS(&GPSSerial);

BMP085 bmp;
float referencePressure = 101325; //Pressure Pascals at sea level
float realPressure, absoluteAltitude, relativeAltitude;

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
float pitch, roll;

ServoStabilizer estabilizacion;

Adafruit_HMC5883_Unified mag;

float scaler;
boolean scaler_flag = false;
float normal_vector_length;
sensors_event_t event; 
float xv, yv, zv;
float calibrated_values[3];

float headingDegrees;
float latitud, longitud, latitudDegs, longitudDegs;
float distanceObjective, bearingObjective;

static const float earthRadius = 6372797.56085; //Meters

/*
 * General telemmetry data: 
 * Fundamentals for AP: Latitud, Longitud, Velocidad, Pitch, Roll, AltitudAP, heading
 * Fundamentals for PADA: circleFound, objectiveLocked, relativeAngle, lensDistance, padaRelease
 */

//Autonomy will not be activated without these data
float valoresTelemetria[3] = {0.0,  //Valor 0 = padaRelease flag
                              0.0,  //Valor 1 = Objective's latitude
                              0.0}; //Valor 2 = Objective's longitude
static const int16_t longitudVector = 3;

//Pueden sacar valores de pitch y roll directamente utilizando estabilizacion.pitchValue() y estabilizacion.rollValue();

void setup() {
  Serial.begin(115200);

  mpu.initialize();
  bmp.begin(BMP085_ULTRA_HIGH_RES);
  mag.begin();
  realPressure = bmp.readPressure();

  Receiver.begin(200000);
  Aileron.attach(29); Elevator.attach(28); Motor.attach(27); Rudder.attach(26); //PWM initialize
  Aileron.writeMicroseconds(1500);
  Elevator.writeMicroseconds(1500);
  Motor.writeMicroseconds(1000);
  Rudder.writeMicroseconds(1500);

  estabilizacion.begin();
  estabilizacion.setGainsRoll(20,0.03,0.02);
  estabilizacion.setGainsPitch(20,0.03,0.02);
  estabilizacion.setAngles(0.0,0.0);
}

void loop() {

  crsf.loop();
  IMU();
  barometer();
  brujula();
  estabilizacion.update(pitch, roll);
  gps();
  LoRaReceiver();

  if (crsf.getChannel(5)>1500){ //Manual operation mode activated. In case of any problem with the autonomy
    Aileron.writeMicroseconds(crsf.getChannel(1));
    Elevator.writeMicroseconds(crsf.getChannel(2));
    Motor.writeMicroseconds(crsf.getChannel(3));
    Rudder.writeMicroseconds(crsf.getChannel(4)); 
  }else{
    if (valoresTelemetria[1] != 0.0 && valoresTelemetria[2] != 0.0){ //Objective's coordinates check.
      //Pre-release route calculations
      distanceObjective = distanceToObjective(latitudDegs, longitudDegs, valoresTelemetria[1], valoresTelemetria[2]);
      bearingObjective = bearingToObjective(latitudDegs, longitudDegs, valoresTelemetria[1], valoresTelemetria[2]);
      if (valoresTelemetria[0] == 1.0){ //Route data is complete. Check if padaRelease switch is activated.
        //Autonomy start
        delay(500); // 500ms wait till electromagnets deactivation
        autonomousMovement();
      }
    }else{ //Manual mode activate if the route is not completed
      Aileron.writeMicroseconds(crsf.getChannel(1));
      Elevator.writeMicroseconds(crsf.getChannel(2));
      Motor.writeMicroseconds(crsf.getChannel(3));
      Rudder.writeMicroseconds(crsf.getChannel(4)); 
    }
  }
  
}
