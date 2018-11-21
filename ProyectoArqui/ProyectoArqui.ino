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
const int IN5 = 8;
const int IN6 = 9;
const int Trig = 6;
const int Echo = 7;
bool derecha = false;
bool izquierda = false;
bool delante = false;
bool atras = false;
//Declaracion de variables
long duracion, distancia;

void setup() {
  Serial.beg in(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
}

void loop() {
  distancia = obstaculo();
  Serial.println(distancia);
  if (distancia <= 10 && distancia >= 1) {
    mover_carro(false, false, false, false);
    mover_sensor(true, false,250);
    mover_sensor(false, true,500);
    mover_sensor(true, false,250);
  } else {
    mover_carro(true, false, true, false);
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
void mover_carro(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
  delay(1200);
}

void mover_sensor(bool in5, bool in6,int tiempo) {
  digitalWrite(IN5, in5);
  digitalWrite(IN6, in6);
  delay(tiempo);
}
