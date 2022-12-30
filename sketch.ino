//define Variables
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 40
#define LCD_LINES   1
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

#define trigerPin 12
#define echoPin 13
#define ledPin 2
#define Ledpin 4
#define speakerPin 10
#define pitch 262

double duration, distance;
void setup() {
  //Setup for Ultrasonic Sensor
  Serial.begin(9600);
  pinMode(trigerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Setup for LED
  pinMode(ledPin, OUTPUT);
  //Setup for Speaker
  pinMode(speakerPin, OUTPUT);
  //Setup for LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 1);
  lcd.print("Theft Alarm System");
  
}

void loop() {
  //Looping Ultrasonic
  digitalWrite(trigerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPin, LOW);
  delayMicroseconds(2);
  //get duration
  duration = pulseIn(echoPin,HIGH);
  //calculate distance
  //distance = time*speed
  distance = (duration/2)*0.0343;

  if(distance<200){
    digitalWrite(ledPin, HIGH);
    digitalWrite(Ledpin, LOW);
    tone(speakerPin, pitch);
    delay(200);
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("Alert  Alert  Alert");
    lcd.print(distance);
    lcd.print("Cm far from door");
    delay(400);
    lcd.clear();
    

    digitalWrite(ledPin, LOW);
    digitalWrite(Ledpin, HIGH);
    noTone(speakerPin);
    delay(300);
  }
  else{
    digitalWrite(ledPin, LOW);
    digitalWrite(Ledpin, LOW);
    noTone(speakerPin);
  }

}
