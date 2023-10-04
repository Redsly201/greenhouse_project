#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

int umid_sol = 0;
int temp = 0;
int umid = 0;

void setup() {
  Serial.begin(9600);

  //VARIABILE GLOBALE PENTRU LOOP:
  

  // PINI NUME DIGITAL WRITE:
  int PIN_BEC = 1;
  int PIN_VENTILATOR = 3;
  int PIN_POMPA = 5;

  // PARAMETRII:
  int TEMPERATURA_MINIMA=16;
  int TEMPERATURA_MAXIMA=40;

  int UMIDITATE_SOL_MINIMA=1200;
  int UMIDITATE_SOL_MAXIMA=350;

  int UMIDITATE_AER_MINIMA=10;
  int UMIDITATE_AER_MAXIMA=95;

  pinMode(PIN_VENTILATOR, OUTPUT);
  pinMode(PIN_POMPA, OUTPUT);
  digitalWrite(PIN_VENTILATOR, LOW);
  digitalWrite(PIN_POMPA, LOW);  
}

void loop() {

  umid_sol = analogRead(0);

  /// AFISARE;  DE INLOCUIT CU AFISARE PE WEB:
  Serial.print("Umiditate sol: ");
  Serial.print(umid_sol);
  Serial.print("\n");

  umid = sensor.readHumidity();
  Serial.print("Humidity:    ");
  Serial.print(sensor.readHumidity(), 2);
  delay(200);
  
  temp = sensor.readTemperature();
  Serial.print("\tTemperature: ");
  Serial.println(sensor.readTemperature(), 2);
  delay(500);
  ///////////// /////////// ////////// ///////// 

  digitalWrite(3, HIGH);
}
  /// LOGICA COMENZI:
/*
  if (temp<(TEMPERATURA_MINIMA+TEMPERATURA_MAXIMA)/2-10)
  {
    ACTION_BEC();
    delay(600000);
    DE_ACTION_BEC();
  }
  else
  {
    if (temp>(TEMPERATURA_MINIMA+TEMPERATURA_MAXIMA)/2+10)
    {
      ACTION_VENTILATOARE();
      delay(600000);
      DE_ACTION_VENTILATOARE();
    }
  }
  
  if(umid_sol>(UMIDITATE_SOL_MINIMA+UMIDITATE_SOL_MAXIMA)/2+100)
  {
    ACTION_POMPE(umid_sol);
  }
  else
    if (umid_sol<(UMIDITATE_SOL_MINIMA+UMIDITATE_SOL_MAXIMA)/2-500)
    {
      ACTION_VENTILATOARE();
      ACTION_BEC();
      delay(600000);
      DE_ACTION_VENTILATOARE();
      DE_ACTION_BEC();
    }
  
}

void ACTION_VENTILATOARE()
{
  digitalWrite(PIN_VENTILATOR, HIGH);
}

void DE_ACTION_VENTILATOARE()
{
  digitalWrite(PIN_VENTILATOR, LOW);
}

void ACTION_POMPE(int umid_sol)
{
  digitalWrite(PIN_POMPA, HIGH);
  delay(2000+umid_sol*5);
  digitalWrite(PIN_POMPA, LOW);
}

void ACTION_BEC ()
{
  digitalWrite(PIN_BEC, HIGH);
}

void DE_ACTION_BEC ()
{
  digitalWrite(PIN_BEC, LOW);
}
*/