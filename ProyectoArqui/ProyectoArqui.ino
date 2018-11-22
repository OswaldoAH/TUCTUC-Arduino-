/**
   Usando Arduino DUE
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
   Jorge Andres Madrid
*/

/**
   Tener en cuenta que estos valores tendrìa que tener para mover el carro
   IN1    IN2     IN3     IN4
   true   false   true    false     Esto para ir hacía adelante
   false  false   true    false     Esto para ir hacía la izquierda
   true   false   false   false     Esto para ir hacía la derecha
   false  false   false   false     Esto para ir hacía atrás
   true   true    true    true      Esto no se hace para evitar quemar el controlar y el arduino.
*/
#include <Servo.h>
//Declaracion de constantes para usar los pines
//Estas variables son para los motores de las llantas.
const int IN1 = 22;
const int IN2 = 23;
const int IN3 = 24;
const int IN4 = 25;
//Estas variables son para controlar lo que es el sensor sonico
const int Trig = 26;
const int Echo = 27;
//Esta variable sirve para controlar la velocidad del motor de las llantas con una salida PWM
const int ENA = 3;
//Estas variables son para el sensor de color
const int s0 = 28;
const int s1 = 29;
const int s2 = 30;
const int s3 = 31;
const int out = 32;
//Esta variable es para lo del sensor de efecto hall para las cajas
const int Hall = 33;
//Declaracion de variables para obtener la distancia que regresa el sensor
long duracion, distancia;
// Variables para el color
int Rojo = 0;
int Verde = 0;
int Azul = 0;
short ColorAnterior = 1;
//Variables para los servos que tenemos
Servo cajas;
//Varaiables booleanas para manejar todo lo de las cajas
bool estado = true;
bool estadohall1;

void setup() {
  //Declaro como se
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(Hall, INPUT);
  cajas.attach(34);
  cajas.write(93);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  delay(3000);
}

void loop() {
  analogWrite(ENA, 140);
  distancia = obstaculo();    //Leemos la distancia a la que esta el carro para girar
  if (distancia <= 15 && distancia >= 1) {  //Si la distancia esta entre 1 y 10 cmts de algo hace lo siguiente.
    analogWrite(ENA, 80);
    while (distancia >= 4) {
      distancia = obstaculo();
      delay(5);
    }
    moverCarro(false, false, false, false);   //Le mandando los 4 parametros como false para que se detenga.
    delay(100);
    int valor = SetColor();
    delay(50);
    Serial.println(valor);
    if (valor == 0) {
      analogWrite(ENA, 140);
      moverCarro(false, true, false, true);     //Le mando los parametros como false, true, false, true para hacer que el carro vaya para atrás
      delay(500);                               //Pongo en modo no operacion durante 500 ms antes de girar a la izquierda
      moverCarro(true, false, false, false);    //Le mando los parametros como (false, false, false, true) para hacer que el carro gire para la izquierda
      delay(800);                               //Pongo en modo no operacion durante 800 ms antes de hacer que el carro pare
      moverCarro(false, false, false, false);   //Le mandando los 4 parametros como false para que se detenga.
      delay(100);
    } else {
      while (!estado) {
        estadohall1 = digitalRead(Hall);
        ColorAnterior = moverCajas(ColorAnterior, valor, estadohall1);
        delay(100);
      }
    }
    //Pongo en modo no operacion durante 100 ms
    //Pongo en modo no operacion durante 100 ms
  } else {                                    //Si la distancia es mayor a 10 cmts hace lo siguiente
    moverCarro(true, false, true, false);     //Le mando los parametros como (true, false, true, false) para hacer que el carro vaya para delante
  }
  //movimiento();
  delay(300);
}

/*
   Función para saber a que distancia esta el carro
   de los objetos retorda un long para saber la distancia
*/
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
/*
   Función para mover el carro
   recibe como parametro 4
   variables booleanas que
   indican si se va a mover
   para delante o para atras.
   izquierda o derecha.
*/
void moverCarro(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
}

int SetColor()
{
  color();

  if (Rojo < Azul && Rojo < Verde && Rojo < 25)
  {
    if (Verde - Azul >= 10 && Verde - Azul <= 25 && Verde - ( 2 * Rojo ) >= 8 )
    {
      Serial.println("Color Rojo");
      estado = false;
      return 1;
    }

    else if (Verde - Rojo <= 10 && Verde - Rojo >= -3 && Azul >= Verde)
    {
      Serial.println("Color Amarillo");
      estado = false;
      return 2;
    }

  } else if (Verde < Rojo && Verde < Azul && Verde < 25)
  {
    Serial.println("Color Verde");
    estado = false;
    return 4;
  }

  else if ((Rojo > Verde &&  Azul < Verde) && Azul < 25 && Rojo > 40)
  {
    Serial.println("Color Azul");
    estado = false;
    return 3;
  } else
  {
    estado = true;
    return 0;
  }
}

void color()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, Rojo
  Rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, Azul
  Azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, Verde
  Verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void mover(int grados)
{
  cajas.write(grados);
}
int moverCajas(int anterior, int entrada, bool sensor) {
  //1 es rojo
  //2 es amarillo
  //3 es azul
  //4 es verde
  //Rojo moviéndose a otro color

  if (anterior == entrada)
  {
    mover(93);
    //soltar();
    //delay(2000);
    estado = true;
    return anterior;
  }
  else
  {
    if (!sensor)
    {
      Serial.print("Anterior: ");
      Serial.println(anterior);
      anterior += 1;
      mover(95);
      delay(50);
      mover(93);
      //estadohall1 == true;
      if (anterior >= 5) anterior = 1;
    }
    else
    {
      mover(95);
    }
    return anterior;
  }
}
