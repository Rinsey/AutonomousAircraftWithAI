///////////////////////////////MORE THAN 100 METERS TO OBJECTIVE FUNCTIONS///////////////////////////////////////
  
void autonomousMovement(){
  
  if(distanceObjective > 100 && relativeAltitude >= 8 && relativeAltitude < 15 && pitch > -1 && pitch < 1){ //CRUISE MODE
    estabilizacion.setAngles(0.0,0.0); //Pitch, Roll
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch()); //Elevator and Ailerons always on middle point
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());   //Turn movement will be affected only with the rudder
    Motor.writeMicroseconds(cruiseSpeed);
  }

  if(distanceObjective > 100 && relativeAltitude < 8){ //ELEVATION TO AVOID ALTITUDE LOST
    estabilizacion.setAngles(5.0,0.0);
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Motor.writeMicroseconds(cruiseSpeed);
  }

  if(distanceObjective > 100  && relativeAltitude > 15){ //DESCENT TO AVOID GAINING ALTITUDE
    estabilizacion.setAngles(-3.0,0.0);
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Motor.writeMicroseconds(cruiseSpeed);
  }
///////////////////////////////100 METERS TO OBJECTIVE REACHED FUNCTIONS///////////////////////////////////////////
  
  if(distanceObjective < 100 && relativeAltitude < 15){ //Landing starts here at 100 meters away from  
    estabilizacion.setAngles(-7.0,0.0);
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Motor.writeMicroseconds(cruiseSpeed - 200);  
  }

  if(distanceObjective < 100 && relativeAltitude < 3){ //Landing starts here at 100 meters away from  
    estabilizacion.setAngles(2.0,0.0);
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Motor.writeMicroseconds(cruiseSpeed);
  }

///////////////////////////////100 METERS TO OBJECTIVE REACHED FUNCTIONS///////////////////////////////////////////
  
  if(distanceObjective < 10 && relativeAltitude < 15){ //Landing starts here at 100 meters away from  
    estabilizacion.setAngles(10.0,0.0);
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Motor.writeMicroseconds(1000); //Motor se apaga
  }

//////////////////////////////RUDDER CORRECTIONS (BEARING = HEADING)///////////////////////////////////////////////////////////////////
  if (headingDegrees > bearingObjective+1){
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());// Roll stabilization stills on here
    Rudder.writeMicroseconds(1300);
    Motor.writeMicroseconds(cruiseSpeed);
  }
  if (headingDegrees < bearingObjective-1){
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());// Roll stabilization stills on here
    Rudder.writeMicroseconds(1700);
    Motor.writeMicroseconds(cruiseSpeed);
  }
}
/* PID
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
     JUGAR CON ESTO   Motor.writeMicroseconds(crsf.getChannel(3));
     JUGAR CON ESTO   Rudder.writeMicroseconds(crsf.getChannel(4));
*/
