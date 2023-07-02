#include "SoftwareSerial.h"
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <String>

SoftwareSerial ph(14, 27);         //rx,tx
SoftwareSerial turbidity(16, 17);  //rx,tx
SoftwareSerial tds(26, 25);        //rx,tx

// String URL = "http://192.168.1.24/iot_sensor/index.php";
const char* ssid = "WifiIndomaret";
const char* password = "selamatdatang";
// const char* ssid = "WifiIndomaret";
// const char* password = "selamatdatang";
const char* server = "http://192.168.152.205/";
// const char* URL = "http://19.168.1.24/mqtt/index.js";
long zero = 0;
long jeda = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ph.begin(9600);
  turbidity.begin(9600);
  tds.begin(9600);

  connectWifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  String data_ph = "";
  String data_turbidity = "";
  String data_tds = "";

  int dat_temp = 25;
  // temp();
  // int peh;

  while (ph.available() > 0) {
    data_ph += char(ph.read());
  }
  while (turbidity.available() > 0) {
    data_turbidity += char(turbidity.read());
  }
  while (tds.available() > 0) {
    data_tds += char(tds.read());
  }
  data_ph.trim();
  // if (millis() - zero > jeda) {
  String URL = String("") + server + "iot_sensor/index.php?tds=" + data_tds + "&ph=" + data_ph+ "&turbidity=" + data_turbidity + "&temp=" + String(dat_temp) ;
  Serial.print("URL: ");
  Serial.println(URL);
  if (data_tds != NULL && data_ph!=NULL){
    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Payload: ");
      Serial.println(payload);
    }
    http.end();
  }else{
    Serial.println('Empty');
  }
  }
  
  Serial.println("+++++++++++++++++++++++++++++++++++");
  
  delay(35000);
  // }
  // Serial.println("Data PH: "+data_ph);
  // Serial.print("Data Turbidity: " + data_turbidity );Serial.println(" NTU");
  // Serial.print("Data TDS: " + data_tds );Serial.println(" PPM");
  // Serial.println("++++++++++++++++");
  // delay(5000);
}

void connectWifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
// void printRandoms(int lower, int upper,
//                             int count)
// {
//     int i;
//     for (i = 0; i < count; i++) {
//         int num = (rand() %
//         (upper - lower + 1)) + lower;
//         printf("%d ", num);
//     }
// }
// void temp(){
//   int lower = 23, upper = 27, count = 1;
 
//     // Use current time as
//     // seed for random generator
//     srand(time(0));
 
//     printRandoms(lower, upper, count);
// }
