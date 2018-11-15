#include <Servo.h> //Valores sin vibración: 0, 169
//Servo modificado para rotación infinita (cajas)
//91 derecha, 95 izquierda
Servo ser1;
Servo caja;
unsigned int angulo;
bool estado;
void setup()
{
  //ser1.attach(12);
  pinMode(42, INPUT);
  caja.attach(41);
  //ser1.write(93);
  caja.write(93);
  Serial.begin(9600);
  Serial.println("ingrese un grado");
}

void loop() 
{
  estado = digitalRead(42); //leer entrada del sensor de efecto hall
  mover_caja(95);
  p_cajas(estado);  
}

void leer_dato()
{
  if(Serial.available() > 0)
  {
    angulo = Serial.parseInt();
    Serial.println(angulo);
  }
}

void p_cajas(bool estado)
{
  mover_caja(95);
  if(!estado)
  {
    mover_caja(93);
    delay(2500);
    estado = true;
  }
}

void mover_caja(int valor)
{
  caja.write(valor);
  delay(50);
}

