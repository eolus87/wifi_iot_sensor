/*********
  Nicolas Gutierrez,
  Heavily influenced by Rui Santos
  https://randomnerdtutorials.com/esp8266-ds18b20-temperature-sensor-web-server-with-arduino-ide/
  https://www.instructables.com/Calibration-of-DS18B20-Sensor-With-Arduino-UNO/
*********/

// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// TO SET UP PER SENSOR
// Replace with your network details
const char* ssid = "YOUR_NETWORK_NAME";
const char* password = "YOUR_NETWORK_PASSWORD";
// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;
// TEMP Correction
const float icing_measure = X;
const float icing_reference = 0;
const float boiling_measure = X;
const float boiling_reference = 99.67; // https://www.omnicalculator.com/chemistry/boiling-point-altitude

// Installation place
const char* installation_place = "XXXXXXX";

// Web Server on port 80
WiFiServer server(80);
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
static char temperatureC_str[7];
const float span_measure = boiling_measure-icing_measure

// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(10000);
  
  // Printing the ESP IP address
  Serial.println(WiFi.localIP());

  // Start the DS18B20 sensor
  sensors.begin();
}

// runs over and over again
void loop() {
  // Listenning for new clients
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n' && blank_line) {
            sensors.requestTemperatures(); 
            // Reading sensor
            float temperatureC = sensors.getTempCByIndex(0);
            // Correcting measure
            temperatureC = (((temperatureC - icing_measure)*boiling_reference)/span_measure) + icing_reference;

            // Check if any reads failed and exit early (to try again).
            if (isnan(temperatureC)) {
              Serial.println("Failed to read from DS18B20 sensor!");
              strcpy(temperatureC_str, "Failed");    
            }
            else{
              dtostrf(temperatureC, 6, 2, temperatureC_str);
              Serial.print(" %\t Temperature: ");
              Serial.print(temperatureC_str);
              Serial.print(" *C ");
            }
            // HTTP Header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            
            // Actual web page
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body><h1>");
            client.println(installation_place);
            client.println("</h1>");
            client.println("<h3>Temp ");
            client.println(temperatureC_str);
            client.println("</h3>");
            client.println("</h3><h3>");
            client.println("</body></html>");     
            break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}