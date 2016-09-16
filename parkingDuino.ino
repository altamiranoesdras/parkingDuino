#include <Servo.h>
Servo myservo;
int boton=2;
int localLed=13;
int sts=0;    

void setup() {
  pinMode(boton,INPUT);
  pinMode(localLed,OUTPUT);
  myservo.attach(9,660,2545);  
  myservo.write(0);   
}

void loop() {
  sts = digitalRead(boton);  // read input value
  
  if (sts == HIGH) {
    digitalWrite(localLed,HIGH);
     myservo.write(90); 
     delay(2000);
     myservo.write(0);
     //myservo.detach(9);
  }else{
    digitalWrite(localLed,LOW);
     delay(20);
  }
}
