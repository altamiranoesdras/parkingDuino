#include <Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

Servo myservo;
int boton=2;
int localLed=13;
int sts=0;
int contador=4;    

void setup() {
  pinMode(boton,INPUT);
  pinMode(localLed,OUTPUT);
  myservo.attach(9,650,2545);  
  myservo.write(180);   

  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Parqueos ");
  lcd.setCursor(0,1);
  lcd.print("Disponibles :");
  lcd.setCursor(14,1);
  lcd.print(contador);
}

void loop() {
  
   sts = digitalRead(boton);  // read input value
  
  if (sts == HIGH) {
    if(contador>0){
      digitalWrite(localLed,HIGH);
      myservo.write(90); 
      delay(2000);
      myservo.write(180);
      contador=contador-1;
      lcd.clear(); 
      lcd.print("Parqueos ");
      lcd.setCursor(0,1);
      lcd.print("Disponibles :");
      lcd.setCursor(14,1);
      lcd.print(contador);
    }
  }else{
     digitalWrite(localLed,LOW);
     delay(20);
  }
}
