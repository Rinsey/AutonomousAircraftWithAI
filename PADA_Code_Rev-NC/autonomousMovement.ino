
void autonomousMovement(){

  if(distanceObjective > 70 && relativeAltitude >= 8){ //Cruise mode started
  
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch()); //Elevator and Ailerons always on middle point
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());   //Turn movement will be affected only with the rudder.
    
    if (headingDegrees > bearingObjective+1){
      Rudder.writeMicroseconds();
    }else if (headingDegrees < bearingObjective-1){
      Rudder.writeMicroseconds();
    }
  }else if(relativeAltitude < 8){
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
    Elevator.writeMicroseconds(1700); //Elevator movement to increas de AOA gaining altitude
  }
  
}

/* PID
    Elevator.writeMicroseconds(1500 - estabilizacion.outputsPitch());
    Aileron.writeMicroseconds(1500 + estabilizacion.outputsRoll());
     JUGAR CON ESTO   Motor.writeMicroseconds(crsf.getChannel(3));
     JUGAR CON ESTO   Rudder.writeMicroseconds(crsf.getChannel(4));
*/
