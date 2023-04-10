
float distanceToObjective(float latitude1, float longitude1, float latitude2, float longitude2){
  
    float haversine; //Variables utilizadas
    float temp;
    float distance; 

    //Pasamos coordenadas a radianes para aplicar Haversine
    latitude1  = latitude1  * PI / 180;
    longitude1 = longitude1 * PI / 180;
    latitude2  = latitude2  * PI / 180;
    longitude2 = longitude2 * PI / 180;

    haversine = (pow(sin((1.0 / 2) * (latitude2 - latitude1)), 2)) + ((cos(latitude1)) * (cos(latitude2)) * (pow(sin((1.0 / 2) * (longitude2 - longitude1)), 2)));
    temp = 2 * asin(min(1.0, sqrt(haversine)));
    distance = earthRadius * temp;

   return distance;
   
}

float bearingToObjective(float lat1, float lon1, float lat2, float lon2) { 

  //Heading is the direction the aircraft is pointing.
  //Bearing is the angle in degrees (clockwise) between North and the direction to the destination or nav aid.
  
  // Calculamos la diferencia entre las coordenadas
  float dLat = lat2 - lat1;
  
  // Calculamos el heading utilizando la fórmula de la dirección inicial
  float x = cos(lat2) * sin(dLat);
  float y = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLat);
  
  float bearing = atan2(x,y) * 180 / PI; //regresamos el bearing en grados
  
  if (bearing < 0) {
    return bearing += 360;
  }else{
    return bearing;
  }
  
}
