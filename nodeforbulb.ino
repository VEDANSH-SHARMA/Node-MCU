
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define WLAN_SSID       "Redmi"
#define WLAN_PASS       "abcdefgh"


void setup(void) {
  

    Serial.begin(115200);
    delay(10);
     Serial.println("Temperature, Humidity"); 
      // Connect to WiFi access point.
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
  pinMode(D0, OUTPUT);
  pinMode(D2, OUTPUT);
}


void postData() {

   WiFiClient client;

   //the path and file to send the data to:
   String urlGet = "/light3";
   
 //Serial.println(a);
 //Serial.print(" ");
  // We now create and add parameters:
  //String src = String(a);
  //String typ = String(b); 
  //String vol =String(l);
  //urlGet += "?voltage=" + vol;

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

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  int payload_value=payload.toInt();
//  Serial.println(httpCode);   //Print HTTP return code
 // Serial.print("payload");
  //Serial.println(payload_value);
//  int payload_value=payload.toInt();
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("payload");
  Serial.println(payload_value);
 
  if(payload_value==11){
    digitalWrite(D0,HIGH);
    digitalWrite(D2,HIGH);
  }
  if(payload_value==0){
    digitalWrite(D0,LOW);
    digitalWrite(D2,LOW);
  }
  if(payload_value==10){
    digitalWrite(D0,HIGH);
    digitalWrite(D2,LOW);
  }
  http.end();  //Close connection
   
}

void loop() {
  
  postData();
 
  delay(10000);
  

}
