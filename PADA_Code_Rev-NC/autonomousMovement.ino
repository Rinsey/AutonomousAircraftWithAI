///////////////////////////////MORE THAN 100 METERS TO OBJECTIVE FUNCTIONS///////////////////////////////////////
  
void autonomousMovement(){
  
  if(distanceObjective > 100 && relativeAltitude >= 8 && relativeAltitude < 15 && pitch > -1 && pitch < 1){ //CRUISE MODE
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch()); //Elevator and Ailerons always on middle point
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());   //Turn movement will be affected only with the rudder
    Motor.writeMicroseconds(cruiseSpeed);
  }

  if(distanceObjective > 100 && relativeAltitude < 8){ //ELEVATION TO AVOID ALTITUDE LOST
    if(pitch > 6){
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1400); //Elevator movement to increas de AOA gaining altitude
    Motor.writeMicroseconds(cruiseSpeed);
    } else if(pitch < 1) {
      Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
      Elevator.writeMicroseconds(1700); //Elevator movement to increas de AOA gaining altitude
      Motor.writeMicroseconds(cruiseSpeed);
    }
    if(pitch < 6 && pitch > 1) {
      Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
      Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
      Motor.writeMicroseconds(cruiseSpeed);
    }
  }

  if(distanceObjective > 100  && relativeAltitude > 15){ //DESCENT TO AVOID GAINING ALTITUDE
    if(pitch > -1){
      Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
      Elevator.writeMicroseconds(1400); //Elevator movement to increas de AOA gaining altitude
      Motor.writeMicroseconds(cruiseSpeed);
    } else if(pitch < -5){
      Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
      Elevator.writeMicroseconds(1700); //Elevator movement to increas de AOA gaining altitude
      Motor.writeMicroseconds(cruiseSpeed);
    }
    if(pitch < -5 && pitch > -1) {
      Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
      Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
      Motor.writeMicroseconds(cruiseSpeed);
    }
  }
///////////////////////////////100 METERS TO OBJECTIVE REACHED FUNCTIONS///////////////////////////////////////////
  
  if(distanceObjective < 100 && relativeAltitude < 8){ //Landing starts here at 100 meters away from  
    if(pitch < -5.5){
       Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
       Motor.writeMicroseconds(cruiseSpeed);
       Elevator.writeMicroseconds(1300);
    }
    if(pitch > -4.5){
       Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
       Motor.writeMicroseconds(cruiseSpeed);
       Elevator.writeMicroseconds(1700);
    }
    if(pitch < -4.5 && pitch > -5.5){
       Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
       Motor.writeMicroseconds(cruiseSpeed);
    }
  }

///////////////////////////////100 METERS TO OBJECTIVE REACHED FUNCTIONS///////////////////////////////////////////
  
  if(distanceObjective < 10 && relativeAltitude < 3){ //Landing starts here at 100 meters away from  
    if(pitch < -5.5){
       Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
       Motor.writeMicroseconds(1000);
       Elevator.writeMicroseconds(1300);
    }
    if(pitch > -4.5){
       Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
       Motor.writeMicroseconds(1000);
       Elevator.writeMicroseconds(1700);
    }
    if(pitch < -4.5 && pitch > -5.5){
       Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
       Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
       Motor.writeMicroseconds(1000);
    }
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
