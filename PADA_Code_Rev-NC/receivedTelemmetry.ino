
void LoRaReceiver (){
  if(reyax.available()){
    String cadenaRecibida = reyax.readString();
    separarCadena(cadenaRecibida); // 0.0,32.000,-115.0000
  }
}

void separarCadena(String cadena) {
  
  int inicio = 0; //Importante para encontrar cada coma en la sentencia
  int finall = 0; // Para marcar la siguiente coma
  int contador = 0; // para insertar el dato ya convertido en su posicion correspondiente es contador

  while (finall >= 0 && contador < longitudVector) { //Se puede cambiar por un for 
    finall = cadena.indexOf(',', inicio); // Encontramos la posicion de una coma, desde el punto de inicio el cual cambia dependiendo de las comas encontradas
    if (finall == -1) { //Esto es en caso de que ya no se encuentre ninguna coma
      finall = cadena.length(); //Si no se encuentra ninguna coma, el fin para el substring seria el final de la cadena o sea su longitud de caracteres
    }
    
    String valorStr = cadena.substring(inicio, finall); //Se extrae el valor entre dos comas.
    inicio = finall + 1; //se establece un nuevo inicio para empezar a buscar las comas y para extraer valores
    float valor = valorStr.toFloat(); //Se convierte a float, aqui pasa algo chido si no se puede regresa un nan el cual se puede comprobar 
    if (!isnan(valor)) { //Aqui comprobamos si el valor se pudo convertir, en caso de que no pues se ignora y se añade un 0
      valoresTelemetria[contador] = valor; //Si el valor si es valido se almacena
      contador++;// se recorre la posicion en la que se guarda el valor.
    }
  }
  
}
