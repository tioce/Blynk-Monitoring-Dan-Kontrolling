#define BLYNK_PRINT Serial
//template ID dan Device name dapat dilihat di Blynk Cloud bagian device
#define BLYNK_TEMPLATE_ID "TMPL6AvBRcEJf"
#define BLYNK_TEMPLATE_NAME "Monitoring"
#define BLYNK_AUTH_TOKEN "7EBUulD6JvEHJJ3wgQvnV-M7GAreDEW6"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h> //Library untuk DHT

char auth[] = BLYNK_AUTH_TOKEN ; //Auth Token
char ssid[] = "NYONYA SIMPING"; //nama hotspot yang digunakan
char pass[] = "12345678910abc"; //password hotspot yang digunakan

#define DHTPIN D2 //deklarasi pin D3 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11
#define LED D3
#define buzzer D4
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//function untuk pengiriman sensor
void sendSensor()
{
float t = dht.readTemperature(); //pembacaan sensor
float h = dht.readHumidity();

//menampilkan temperature pada Serial monitor
Serial.print("% Temperature: ");
Serial.print(t);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(h);
Serial.println("% ");

Blynk.virtualWrite(V0, t); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V1, h); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud

}
BLYNK_WRITE(V2)
{
int pinValue = param.asInt();
digitalWrite(LED,pinValue);
}
BLYNK_WRITE(V3)
{
int pinValue1 = param.asInt();
digitalWrite(buzzer,pinValue1);
}
void setup()
{
// Debug console
pinMode(LED,OUTPUT);
pinMode(buzzer,OUTPUT);
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
Blynk.begin(auth, ssid, pass); //memulai Blynk
dht.begin(); //mengaktifkan DHT11
timer.setInterval(1000L, sendSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}

void loop()
{
Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}