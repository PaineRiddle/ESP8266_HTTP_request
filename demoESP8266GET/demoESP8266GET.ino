#include <SoftwareSerial.h>

SoftwareSerial wifi(6, 7); // RX, TX
String comdata = ""; //get from wifi rx,tx

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Connected!");
  wifi.begin(9600);
}

//read wifi rx,tx
void getComdata()
{
  while (wifi.available() > 0) {
    comdata += char(wifi.read());
    delay(2);
  }
}

int f = 0;
void loop() {
  if (f == 0) {
    delay(1000);
    postHTTP();
    f = 1;
  }

  getComdata();
  if (comdata.length() > 0) {
    Serial.print(comdata);
    comdata = "";
  }
  if (Serial.available()) {
    wifi.write(Serial.read());
  }

}

void postHTTP()
{
  wifi.println("AT+CIPSTART=\"TCP\",\"www.zhangtory.com\",80");
  delay(1000);
  getComdata();
  if (comdata.length() > 0) {
    Serial.println(comdata);
    comdata = "";
  }
  //send date to 8266
  wifi.println("AT+CIPSEND");
  delay(2000);
  getComdata();
  if (comdata.length() > 0) {
    Serial.println(comdata);
    comdata = "";
  }
  wifi.println("GET http://zhangtory.com HTTP/1.0\r\n\r\n\r\n");
  wifi.println("");
  delay(2000);
  getComdata();
  if (comdata.length() > 0) {
    Serial.println(comdata);
    comdata = "";
  }
  wifi.print("+++");
  delay(100);
  wifi.println("");
  delay(500);
  getComdata();
  if (comdata.length() > 0) {
    Serial.println(comdata);
    comdata = "";
  }
  wifi.println("AT+CIPCLOSE");//close TCP
  delay(1000);
  getComdata();
  if (comdata.length() > 0) {
    Serial.println(comdata);
    comdata = "";
  }
}

