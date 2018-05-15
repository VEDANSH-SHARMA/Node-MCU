//#include <DHTesp.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define WLAN_SSID       "Redmi"
#define WLAN_PASS       "abcdefgh"
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
//IP or name of address root: ie: google.com
//NOT google.com/nothing/after/the/dotcom.html


#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 
//unsigned long time;
unsigned long int milli_time;
void setup(void)
{ 
  dht.begin();
  Serial.begin(115200);
  //Serial.println("Humidity and temperature\n\n");
  //delay(700);
   Serial.println("CLEARDATA");        //This string is defined as a 
                                      // commmand for the Excel VBA 
                                      // to clear all the rows and columns
  Serial.println("Temperature, Humidity");  
                                      //LABEL command creates label for 
                                      // columns in the first row with bold font
                                      Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: ")); Serial.println(WiFi.localIP());
}

void postData(float a, float b) {

   WiFiClient client;

   //the path and file to send the data to:
   String urlGet = "/jsondata";
   //milli_time=millis();  
//    float h = dht.readHumidity();
//    float t = dht.readTemperature();  
//    Serial.print(t);
//    Serial.print(",");
//     Serial.print(h);
//    Serial.print(",");
 float sensorValue = analogRead(A0);
 float l = sensorValue * (5.0 / 1023.0);
 //float l=100;
 Serial.println(l);
 Serial.print(" ");
 //Serial.println(a);
 int c =(int) a;
 int d =(int)  b;
 int e =(int)  l;
 Serial.print(" ");
  // We now create and add parameters:
  String src = String(c);
  String typ = String(d); 
  String valLdr =String(e);
  urlGet += "?temp=" + src + "&humid=" + typ + "&valLdr=" + valLdr;
  
  HTTPClient http;    //Declare object of class HTTPClient

  String ADCData, station, postData;
  int adcvalue = 123; //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversion
  station = "A";

  //Post Data
  //postData = '{"humid": ADCData,"temp":station}';
  String URI = "https://trusty-lock-198106.appspot.com" + urlGet;

  http.begin(URI,"b83d313e2d85ed8c3aa56c68f7e563633de8c5e3");              //Specify request destination
  //http.addHeader("Content-Type", "application/json\r\n");    //Specify content-type header

  //int httpCode = http.POST(postData);   //Send the request
  int httpCode = http.GET();
  String payload = http.getString();    //Get the response payload

  //Serial.println(httpCode);   //Print HTTP return code
  //Serial.println(payload);    //Print request response payload
  int payload_value=payload.toInt();
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("payload");
  Serial.println(payload_value);
  
  http.end();  //Close connection
   
}


void loop() {
    milli_time=millis();  
    float h = dht.readHumidity();
    float t = dht.readTemperature();   
   // Serial.print(milli_time);      
   // Serial.print(",");
    //Serial.print("temperature = ");
    Serial.print(t); 
    //Serial.println("C  ");
    Serial.print(",");
    //Serial.print("humidity = ");
    Serial.print(h);
    //Serial.print("%  ");
    Serial.print(",");
    postData(t,h);

    delay(5000);

    // read the input on analog pin 0:
 // int sensorValue = analogRead(A0);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //float voltage = sensorValue * (5.0 / 1023.0);
  
  // print out the value you read:
 //Serial.println(voltage);
  //Serial.println(sensorValue);
  delay(5000);
  
}
