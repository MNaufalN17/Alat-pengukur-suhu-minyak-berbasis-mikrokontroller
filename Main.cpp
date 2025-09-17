#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "max6675.h"

// --- Pin MAX6675 ---
int thermoSO = 19;   // MISO
int thermoCS = 5;    // CS
int thermoSCK = 18;  // SCK

MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

unsigned long lastRead = 0;

//PIN BUZZER
int buzz = 15;

// --- LCD I2C ---
LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat 0x27, 16 kolom, 2 baris

void setup() {
  Serial.begin(9600);
  delay(500);

  // Init LCD
  Wire.begin(21, 22); // SDA=21, SCL=22
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Kontrol Suhu");
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, HIGH);
  delay(1000);
  digitalWrite(buzz, LOW);
}

void loop() {
  double suhu = thermocouple.readCelsius();

  if (millis() - lastRead >= 200) {  // setiap 200 ms baca data
    lastRead = millis();}

  // Serial monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  // Tampil di LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Suhu:");
  lcd.setCursor(6,0);
  lcd.print(suhu, 1); // 1 angka desimal
  lcd.print("C");

  //CEK SUHU
  if(suhu <= 70){
    lcd.setCursor(0,1);
    lcd.print("SUHU KURANG"); // 1 angka desimal
    digitalWrite(buzz, LOW); // matikan buzzer
    }
   else if(suhu >= 70 && suhu <= 80){
    lcd.setCursor(0,1);
    lcd.print("SUHU NORMAL"); // 1 angka desimal
    digitalWrite(buzz, LOW); // matikan buzzer
    }
   else if(suhu > 90 ){
    lcd.setCursor(0,1);
    lcd.print("SUHU TINGGI"); // 1 angka desimal

    digitalWrite(buzz, HIGH);
    delay(60000);
    digitalWrite(buzz, LOW);
    delay(30000);

    }
   else{
    digitalWrite(buzz, LOW); // matikan buzzer
    }

  delay(250);

}
