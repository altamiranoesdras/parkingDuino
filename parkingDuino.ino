#include <Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

//Objeto para manejar LCD
LiquidCrystal_I2C lcd(0x3F,16,2);
//Objeto para manejar el servo motor
Servo myservo;

int localLed=13;
int boton=2;
int sts=0;
int p1=3,p2=4,p3=5,p4=6;

int contador=4;
int msFrenteSensor=0;

#define Pecho 10
#define Ptrig 11
long duracion, distancia; 

void setup() {
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)

  pinMode(boton,INPUT);
  pinMode(p1,INPUT);
  pinMode(p2,INPUT);
  pinMode(p3,INPUT);
  pinMode(p4,INPUT);
  
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

  //Estado del boton para solicitar entrada
  sts= digitalRead(boton);  

  if (sts== HIGH) {
    
    if(myservo.read()==180){
      digitalWrite(localLed,HIGH);
      myservo.write(90); 
      //delay(2000);
      //myservo.write(180);
      //contador=contador-1;
    }
  }else{
     digitalWrite(localLed,LOW);
     delay(20);
  }

  if(myservo.read()==90){
    distancia= echoLocaliza();

    if (distancia <= 10 && distancia >= 1){
      Serial.println("Vehiculo frente a sensor");         // envia la palabra Alarma por el puerto serial
      msFrenteSensor++;
    }

    if(msFrenteSensor > 10 && distancia >= 11){
        Serial.println("Paso");         // envia la palabra Alarma por el puerto serial
        myservo.write(180); 
        delay(20);
        msFrenteSensor=0;
        contador--;
        muestraDisponibles(contador);
    }
  }
}

long echoLocaliza(){
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros

  if (distancia >= 500 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");                  // no mide nada
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
    digitalWrite(13, 0);               // en bajo el pin 13
  }

  return distancia;
}


void muestraDisponibles(int contador){
  lcd.clear(); 
  lcd.print("Parqueos ");
  lcd.setCursor(0,1);
  lcd.print("Disponibles :");
  lcd.setCursor(14,1);
  lcd.print(contador);  
}
