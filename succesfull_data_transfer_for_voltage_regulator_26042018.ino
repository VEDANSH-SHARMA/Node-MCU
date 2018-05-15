
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define WLAN_SSID       "Redmi"
#define WLAN_PASS       "abcdefgh"

//unsigned long time;


void setup(void) {
  
    
    Serial.begin(115200);
    delay(10);
     //Serial.println("Temperature, Humidity"); 
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
}


void postData() {

   WiFiClient client;

   //the path and file to send the data to:
   String urlGet = "/voltage";
    String urlGet2 = "/thermo"; 
 float inverterValue = analogRead(A0);
 float l = inverterValue * (5.0 / 1023.0);
  
 Serial.println(l);
 Serial.print(" ");
 //Serial.println(a);
 //Serial.print(" ");
  // We now create and add parameters:
  //String src = String(a);
  //String typ = String(b); 
  int k=(int) l;
  k=k*1; 
  Serial.println(k);
  String vol =String(k);
  urlGet += "?voltage=" + vol;
  //urlGet2 += "?=" + vol;
    HTTPClient http;    //Declare object of class HTTPClient
    HTTPClient http2;    //Declare object of class HTTPClient
 
  String ADCData, station, postData;
  int adcvalue = 123; //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversion
  station = "A";

  //Post Data
  //postData = '{"humid": ADCData,"temp":station}';
  String URI = "https://trusty-lock-198106.appspot.com" + urlGet;
  String URI2 = "https://trusty-lock-198106.appspot.com" + urlGet2;
  
  http.begin(URI,"b83d313e2d85ed8c3aa56c68f7e563633de8c5e3");              //Specify request destination
  //http.addHeader("Content-Type", "application/json\r\n");    //Specify content-type header
  http2.begin(URI2,"1767d07c11aad99b288016105688b1ba0ba041cd");              //Specify request destination
  
  //int httpCode = http.POST(postData);   //Send the request
  int httpCode = http.GET();
  String payload = http.getString();    //Get the response payload
  int httpCode2 = http2.GET();
  String payload2 = http2.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  int payload_value=payload.toInt();
  //Serial.println(httpCode);   //Print HTTP return code
  Serial.print("payload");
  Serial.println(payload_value); 


  Serial.println(httpCode2);   //Print HTTP return code
  Serial.println(payload2);    //Print request response payload
  int payload_value2=payload2.toInt();
  //Serial.println(httpCode);   //Print HTTP return code
  Serial.print("payload");
  Serial.println(payload_value2);
  if(payload_value2==1){
    digitalWrite(D0,HIGH);
  }
  else if(payload_value2==2){
    digitalWrite(D0,LOW);
  }
  
  http.end();  //Close connection
  http2.end();
}

void loop() {
 
  postData();

  delay(10000);

}
