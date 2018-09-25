/**
   Prueba demovimiento con
   HC-SR04 para esquivar objetos
   20-09-2018
   Universidad Rafael Landivar
   Héctor Armando Tello Itzep
   Lilian Nahomi Torres Gonzalez
   Erick Alexander de León Veliz
   Mynor Oswaldo Alvarez Hernández
   Pedro Abraham Cotoc Bustamante
   Mario Enrique Castañeda Plato
*/
//Declaracion de constantes para usar los pines
const int IN1 = 5;
const int IN2 = 4;
const int IN3 = 3;
const int IN4 = 2;
const int Trig = 6;
const int Echo = 7;
//Declaracion de variables
long duracion, distancia;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
}

void loop() {
  distancia = obstaculo();
  Serial.println(distancia);
  if (distancia <= 10 && distancia >= 1) {
    mover(true, false, false, false);
  } else {
    mover(true, false, true, false);
  }
  delay(400);
  //movimiento();
}
long obstaculo() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duracion = pulseIn(Echo, HIGH);
  distancia = (duracion / 2) / 29;
  return distancia;
}
void mover(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
  delay(1200);
}
