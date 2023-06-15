#include <Servo.h>

//  temperature & lux
#define TMP36_INPUT 0
#define CDS_INPUT 1

// I2C 통신 라이브러리 설정 
#include <Wire.h>
// I2C LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>
 

Servo motor1;
int servoMotorPin = 9;
LiquidCrystal_I2C lcd(0x27,16,2);
int motorAngle;
int motorAngleOld;

void setup() {
  Serial.begin(9600);

  const int CDSPin = 1;
  const int TMPPIN = 0;
  const int potentioMeterPin = 3;
  lcd.init();
  lcd.backlight();
  lcd.print("ex 6.2");
  lcd.setCursor(0,1);
  lcd.print(" Test");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("temp :  ");
  lcd.setCursor(0,1);
  lcd.print("lux : ");
  lcd.setCursor(15,1);
  lcd.print("");

  motor1.attach(servoMotorPin,600,2400);
}

void loop() {
  // Temperature from TMP36
  int temp_value = analogRead(TMP36_INPUT);
  // converting that reading to voltage
  float voltage = temp_value * 5.0 * 1000;  // in mV
  voltage /= 1023.0;
  float tempC = (voltage - 500) / 10 ;

  // Lux from CdS (LDR)
  int cds_value = analogRead(CDS_INPUT);
  int lux = int(luminosity(cds_value));
//  Serial.print("ARnn,");
  Serial.print(tempC);
  Serial.print(",");
  Serial.println(lux);
  
  delay(1000);

  lcd.setCursor(9,0);
  lcd.print("   ");
  lcd.setCursor(9,0);
  lcd.print(tempC);

  lcd.setCursor(13,1);
  lcd.print("  ");


  lcd.setCursor(12,1);  
  lcd.print(lux);
  delay(1000);
  
  
  if(tempC >25){
    motor1.write(360);
    delay(100);
  }

}

//Voltage to Lux
double luminosity (int RawADC0){
  double Vout=RawADC0*5.0/1023.0;  // 5/1023 (Vin = 5 V)
  double lux=(2500/Vout-500)/10.0;  
  // lux = 500 / Rldr, Vout = Ildr*Rldr = (5/(10 + Rldr))*Rldr
  return lux;
}


