#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define SDA_PIN D4
#define SCL_PIN D3

const char* ssid = "CNOG-Penthouse";
const char* password = "1234567890";

ESP8266WebServer server(80);

const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;

WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org");


int hours=0;
int minutes=0;


float temperature = 25.0;
float humidity = 70.0;

void setup() {
    // Initialize Serial Monitor

    Wire.begin(SDA_PIN, SCL_PIN, I2C_MASTER); // Initialize I2C communication as master
    
    Serial.begin(9600);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Define web routes
    server.on("/", HTTP_GET, handleRoot);
    server.on("/add", HTTP_POST, handleAdd);

    // Start the server
    server.begin();
    Serial.println("HTTP server started");
        Serial.print("Adresa IP: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();
    timeClient.setTimeOffset(0); // Adjust the time offset if needed
  
  String dataToSend = "Test"; // Data to send as a string
      Wire.beginTransmission(I2C_SLAVE); // Start communication with slave at address 0x8
      Wire.write(dataToSend.c_str()); // Send data to slave
      Wire.endTransmission(); // End communication
}

void loop() {
  server.handleClient();
  timeClient.update();
  String currentTime = timeClient.getFormattedTime(); // Get the time as a formatted string
  int currentHour;
  int currentMinute;
  //Serial.print("Current time: ");
  //Serial.println(currentTime);

  // Extract hours and minutes
  sscanf(currentTime.c_str(), "%d:%d", &currentHour, &currentMinute);
  
  if (currentHour>21)
    currentHour = currentHour + 3 - 24;
  else
    currentHour += 3;
  if (currentHour==24)
    currentHour = 0;
  Serial.print("Current hour: ");
  Serial.println(currentHour);
  Serial.print("Set hour: ");
  Serial.println(hours);
  Serial.print("Current minute: ");
  Serial.println(currentMinute);
  Serial.print("Set minute: ");
  Serial.println(minutes);

  if (currentHour == hours)
  {
    if (currentMinute == minutes)
    {
      Serial.print (" AM INTRAT AM INTRAT AM INTRAT !!!!");
      Serial.print (" AM INTRAT AM INTRAT AM INTRAT !!!!");
      Serial.print (" AM INTRAT AM INTRAT AM INTRAT !!!!");
      server.handleClient();
      String dataToSend = "Test"; // Data to send as a string
      Wire.beginTransmission(I2C_Slave); // Start communication with slave at address 0x8
      Wire.write(dataToSend.c_str()); // Send data to slave
      Wire.endTransmission(); // End communication
    }
  }
  /*
  if(!(millis()%3000))
  {
    Wire.requestFrom(I2C_SLAVE, 1);    // request 1 byte from Arduino slave device #8
    temperature = Wire.read(); 
    Serial.println(temperature);
    Serial.println(" ");
  }*/
  delay(2000);
}

void handleRoot() {
    // Serve the HTML dashboard
    String html = "<html><head><link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Roboto:300,400,500,700&display=swap'>";
    html += "<style>";
    html += "body {font-family: 'Roboto', sans-serif; background-color: #f5f5f5;}";
    html += "h1 {background-color: #4fcc02; color: #fff; padding: 20px; border: 2px solid #000; border-radius: 10px;}";
    html += "h2 {color: #4fcc02;}";
    html += "table {width: 100%; border-collapse: collapse; background-color: #fff;}";
    html += "th, td {padding: 8px; text-align: left; border-bottom: 1px solid #ddd;}";
    html += "form {margin-top: 20px;}";
    html += "label {font-weight: bold;}";
    html += "input[type='time'], select, input[type='submit'] {width: 100%; padding: 10px; margin: 10px 0;}";
    html += "input[type='submit'] {background-color: #4fcc02; color: #fff; border: 2px solid #000; border-radius: 5px; cursor: pointer;}";
    html += "input[type='submit']:hover {background-color: #3fa701;}";
    html += "</style></head><body>";
    html += "<h1>Dashboard</h1>";

    html += "<h1>Schedule Interface</h1>";
    html += "<form action='/add' method='POST'>";
    html += "<label for='time'>Time:</label>";
    html += "<input type='time' id='time' name='time' required><br><br>";
    html += "<input type='submit' value='Add Schedule'>";
    html += "</form>";

    // Ground Humidity section
    html += "<h2>Ground Humidity</h2>";
    html += "<table>";
    html += "<tr><th>Sensor</th><th>Value (%)</th></tr>";
    html += "<tr><td>Sensor 1</td><td>"  +String(humidity) + "%</td></tr>";
    html += "</table>";

    // Temperature section
    html += "<h2>Temperature</h2>";
    html += "<table>";
    html += "<tr><th>Sensor</th><th>Value (°C)</th></tr>";
    html += "<tr><td>Sensor 1</td><td>" + String(temperature) + "°C</td></tr>";
    html += "</table>";

    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleAdd() {
    // Retrieve data from the POST request
    String time = server.arg("time");

    // Print the received data to the serial monitor
    
    Serial.print("Received Time: ");
    Serial.println(time);
    /*
    server.handleClient();
    String dataToSend = time; // Data to send as a string
    Wire.beginTransmission(0x08); // Start communication with slave at address 0x8
    Wire.write(dataToSend.c_str()); // Send data to slave
    Wire.endTransmission(); // End communication
    */

    String timeStr = time; // Replace with your time string

    char* str = strdup(timeStr.c_str()); // Convert String to C-style string
    char* token = strtok(str, ":"); // Split the string using ":"

    if (token != NULL) {
        hours = atoi(token); // Convert the first part to an integer
        token = strtok(NULL, ":"); // Get the next part

        if (token != NULL) {
            minutes = atoi(token); // Convert the second part to an integer
            Serial.print("Hours: ");
            Serial.println(hours);
            Serial.print("Minutes: ");
            Serial.println(minutes);
        } else {
            Serial.println("Invalid time format.");
        }
    } else {
        Serial.println("Invalid time format.");
    }

    free(str); // Free the allocated memory

    // Send a JavaScript alert to display a pop-up message in the browser
    String jsScript = "<script>alert('Schedule entry added'); window.location='/';</script>";
    server.send(200, "text/html", jsScript);
}