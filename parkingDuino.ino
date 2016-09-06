#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int boton=2;
int sts=0;
int val;    // variable to read the value from the analog pin

void setup() {
  pinMode(boton,OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);                  // sets the servo position according to the scaled value
}

void loop() {
  sts = digitalRead(boton);  // read input value
  if (sts == HIGH) {
     myservo.write(90); 
     delay(2000);
     myservo.write(0); 
  }
  
  
}
