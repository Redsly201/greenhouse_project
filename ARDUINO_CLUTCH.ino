#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht = DHT(DHTPIN, DHTTYPE);

float t = 0;
float h = 0; 

char receivedData[255]; // Buffer to store received data

  int PIN_VENTILATOR = 3;
  int PIN_POMPA = 5;

void setup() {
  Wire.begin(0x08); // Set slave address to 0x08
  Wire.onReceive(receiveEvent); // Register the receive event
  Serial.begin(9600);
  
t = dht.readTemperature() ; 
h = dht.readHumidity();
}

void loop() {
  if (!(millis() % 300000))
  {
    t = dht.readTemperature() ; 
    h = dht.readHumidity();
  }
  
  // Your main loop code here
}

void receiveEvent(int byteCount) {

  int i = 0;
  Serial.print("test");
  while (Wire.available()) {
    receivedData[i++] = Wire.read(); // Read the data sent by the master
  }
   Serial.print("test2");
  receivedData[i] = '\0'; // Null-terminate the received data as a string
  Serial.print("Received: ");
  Serial.println(receivedData);

  
  digitalWrite(PIN_POMPA, HIGH);
  delay(3000);
  digitalWrite(PIN_POMPA, LOW); 
}

void requestEvent()
{
  int temptemp = t;
  Wire.write(temptemp);  
}