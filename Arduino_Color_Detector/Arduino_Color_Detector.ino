// TCS230 pins connected to Arduino
#include <Servo.h>
const int s0 = 36;
const int s1 = 37;
const int s2 = 38;
const int s3 = 39;
const int out = 40;
const int Hall =42;
// Variables
int Rojo = 0;
int Verde = 0;
int Azul = 0;
short ColorAnterior = 1;
Servo cajas;
bool estado = true;
bool estadohall1;
void setup()
{
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(Hall,INPUT);
  cajas.attach(41);
  cajas.write(93);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

void loop()
{
  int valor=SetColor();
  while(!estado){
    estadohall1= digitalRead(Hall);
    ColorAnterior = moverCajas(ColorAnterior,valor,estadohall1);
    delay(100);
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
      estado=false;
      return 1;
    }

   else if (Verde - Rojo <= 10 && Verde - Rojo >= -3 && Azul >= Verde)
    {
      Serial.println("Color Amarillo");
      estado=false;
      return 2;
    }

  } else if (Verde < Rojo && Verde < Azul && Verde < 25)
  {
    Serial.println("Color Verde");
    estado=false;
    return 4;
  }

  else if ((Rojo > Verde &&  Azul < Verde) && Azul < 25 && Rojo > 40)
  {
    Serial.println("Color Azul");
    estado=false;
    return 3;
  }else
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
/*void p_cajas(bool estado)
{
  if(!estado)
  {
    mover_caja(ColorAnterior, valor);
    delay(2500);
    estado = true;
  }
}*/
int moverCajas(int anterior, int entrada, bool sensor) {
  //1 es rojo
  //2 es amarillo
  //3 es azul
  //4 es verde
  //Rojo moviéndose a otro color
        
  if(anterior == entrada)
  {
    mover(93);
    //soltar();
    //delay(2000);
    estado = true;
    return anterior;
  }
  else
  {
    if(!sensor)
    {
      Serial.print("Anterior: ");
      Serial.println(anterior);
      anterior +=1;

        mover(95);
        delay(50);
        mover(93);      
        //estadohall1 == true;
      if(anterior >= 5) anterior = 1;
    }
    else
    {
      mover(95);   
    }
    return anterior;
  }
}
