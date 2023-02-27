#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Servo.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <NTPClient.h>

#define FIREBASE_HOST "amina-iot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "v3SGf9jUoHw58KIDg8gkZ7xKwJ3NU3gjMCwFSN1B"
#define WIFI_SSID "wifi name"     //provide ssid (wifi name)
#define WIFI_PASSWORD "password"  //wifi passwordvoid setup()
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.ubuntu.com", 123, 60000);

Servo rampa1;
int senzorUlaz = D1;
int senzorIzlaz = D5;
int s1 = D2;
bool s1_zauzeto = false;
String vrijemeUlaska, vrijemeIzlaska;
int hh, mm, ss;
bool parking1;
bool rezervisi = false;
int brojMjesta = 2;
int ledPin = D7;
int brojac = 0;
bool rampaRezervacija;
String h, m;
bool ulazniSenzorVrijednost, izlazniSenzorVrijednost;
int brojSlobodnih;

void setup() {
  rampa1.attach(D0);
  rampa1.write(0);
  Serial.begin(9600);  // connect to wifi.
  timeClient.begin();
  pinMode(ledPin, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed()) {
    Serial.print(Firebase.error());
  } else {
    Serial.println("Firebase Connected");
  }
}

void loop() {
  timeClient.update();
  hh = timeClient.getHours() + 1;
  mm = timeClient.getMinutes();
  ss = timeClient.getSeconds();
  h = String(hh);
  m = String(mm);
  h + " :" + m;
  brojSlobodnih = Firebase.getInt("BrojSlobodnih");
  dioda = Firebase.getBool("BrojSlobodnih");
  if (brojSlobodnih == 1) {
    brojac = 1;
  } else {
    brojac = 0;
  }
  Wait for one second
  delay(1000);
  if (brojac == 0) {
    digitalWrite(ledPin, HIGH);

  } else {
    digitalWrite(ledPin, LOW);
  }
  parking1 = digitalRead(s1);

  ulazniSenzorVrijednost = !digitalRead(senzorUlaz);
  izlazniSenzorVrijednost = !digitalRead(senzorIzlaz);

  if (ulazniSenzorVrijednost == 1 && brojac == 0) {  // if high then count and send data
    if (brojac != brojMjesta) {
      brojac = brojac + 1;  //increment count
      Firebase.setInt("BrojSlobodnih", brojac);

      rampa1.write(50);
      delay(1000);

      vrijemeUlaska = h + " :" + m;
      Firebase.setString("VrijemeUlaska1", vrijemeUlaska);
      Firebase.setString("VrijemeIzlaska1", "-");
    }
    Serial.print("brojac");
    Serial.print(brojac);
  } else {
    rampa1.write(0);
  }
  if (izlazniSenzorVrijednost == 1) {  // if high then count and send data
    if (brojac > 0) {
      brojac = brojac - 1;
      Firebase.setInt("BrojSlobodnih", brojac);
    }
    rampa1.write(50);
    delay(1000);
    vrijemeIzlaska = h + " :" + m;
    Firebase.setString("VrijemeIzlaska1", vrijemeIzlaska);

    Serial.print("brojac");
    Serial.print(brojac);
  } else {
    rampa1.write(0);
  }

  rezervisi = Firebase.getInt("rezervacija");

  rampaRezervacija = Firebase.getBool("rampa");

  if (rampaRezervacija == 1) {
    rampa1.write(50);
    delay(1000);
    brojac = 0;
    Firebase.setBool("rampa", 0);
    vrijemeUlaska = h + " :" + m;
    Firebase.setString("VrijemeUlaska1", vrijemeUlaska);
    Firebase.setString("VrijemeIzlaska1", "-");
  }

  Serial.print(rezervisi);
}
