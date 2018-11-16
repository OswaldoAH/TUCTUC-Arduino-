// TCS230 pins connected to Arduino
#include <Servo.h>
const int s0 = 36;
const int s1 = 37;
const int s2 = 38;
const int s3 = 39;
const int out = 40;
const int Hal1 =42;
// Variables
int Rojo = 0;
int Verde = 0;
int Azul = 0;
short ColorAnterior = 1;
Servo cajas;
bool estado = true;
void setup()
{
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(Hal1,INPUT);
  cajas.attach(41);
  cajas.write(93);
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

void loop()
{
  int valor=SetColor();
  while(!estado)
  {
    mover(45);
    estado = digitalRead(Hall);
    ColorAnterior = moverCajas(ColorAnterior, valor);
  }
}

void mover(int grados)
{
  cajas.write(grados);
}

int SetColor()
{
  color();
  
  if (Rojo < Azul && Rojo < Verde && Rojo < 25)
  {
    if (Verde - Azul >= 10 && Verde - Azul <= 25 && Verde - ( 2 * Rojo ) >= 8 )
    {
      Serial.println("Color Rojo");
      return 1;
    }

   else if (Verde - Rojo <= 10 && Verde - Rojo >= -3 && Azul >= Verde)
    {
      Serial.println("Color Amarillo");
      return 2;
    }

  } else if (Verde < Rojo && Verde < Azul && Verde < 25)
  {
    Serial.println("Color Verde");
    return 4;
  }

  else if ((Rojo > Verde &&  Azul < Verde) && Azul < 25 && Rojo > 40)
  {
    Serial.println("Color Azul");
    return 3;
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
void p_cajas(bool estado)
{
  if(!estado)
  {
    mover_caja(ColorAnterior, valor);
    delay(2500);
    estado = true;
  }
}
int moverCajas(int anterior, int siguiente) {
  //1 es rojo
  //2 es amarillo
  //3 es azul
  //4 es verde
  //Rojo moviéndose a otro color
  if(anterior == 1) {
    switch(siguiente){
      case 2: //Mover a amarillo
        mover(95);
        anterior = 2;
        break;
      case 3: //Mover a azul
        mover(95);
        anterior = 3;
        break;
      case 4:  //Mover a verde
        mover(91);
        anterior = 4;
        break;
      default:
        delay(2500);
    }
    return anterior;
  }
}
