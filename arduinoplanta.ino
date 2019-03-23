const int botonStar = 13;
const int botonStop = 12;
const int botonReset = 11;
const int banda = 8 ;
const int valvula = 7;
const int trigger = 9;
const int echo = 10;
int distancia = 2;


/*# Banda
# Sensor
# Para
# Llena
# Banda
*/


void setup() {

  Serial.begin(9600);

  // Pines del sistema
  // Banda
  pinMode(banda, OUTPUT);

  //Valvula
  pinMode(valvula, OUTPUT);


  //Sonar
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  //Ejecuciones Iniciales del sistema

  // paramos la banda y la valvula enviando un activo bajo
  digitalWrite(banda, LOW);
  digitalWrite(valvula, LOW);



}

int sonar(){
    long t;
    //se apaga el pulso para no generar interferencias.
    digitalWrite(trigger, LOW);
    //tiempo que dura el pulso apagado 2microsegundos
    delayMicroseconds(2);
    // se enciende el pulso durante 10microsegundos
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    // se apaga el pulso
    digitalWrite(trigger, LOW);
    t = pulseIn(echo, HIGH);
    distancia= t/58;
    Serial.print(distancia);
    Serial.print("\n");
    delay(500);
    return distancia;
  }


void llenar(){
  digitalWrite(valvula, HIGH);
  Serial.print("Llenando");
  Serial.print("\n");
  delay(5000);
  digitalWrite(valvula, LOW);
  Serial.print("Para llenado");
  Serial.print("\n");
  }





void loop() {

Serial.print("Moviendo banda");
Serial.print("\n");
digitalWrite(banda, HIGH);
distancia = sonar();
  if(distancia<=25 && distancia >= 3){
    Serial.print("Distancia: "+ distancia);
    Serial.print("\n");
    delay(2000);
    digitalWrite(banda, LOW);
    Serial.print("Llego tarro");
    Serial.print("\n");
    llenar();
    digitalWrite(banda, HIGH);
    delay(8000);
  }

}
