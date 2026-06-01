// C++ code
//UNFINISHED SEGREGATOR PROJECT PROTOTYPE

#include <Servo.h>

const int trigPinHatch = 9;
const int echoPinHatch = 10;

const int trigPinMain = 6;
const int echoPinMain = 7;

int servoHatch = 3;
int servoMain = 5;

Servo servo1;
Servo servo2;

long duration;
long durationL;
int distance;
int distanceL;

bool done = false, in = false;

void setup()
{
  pinMode(trigPinHatch, OUTPUT);
  pinMode(echoPinHatch, INPUT);
  pinMode(trigPinMain, OUTPUT);
  pinMode(echoPinMain, INPUT);
  servo1.attach(servoHatch);
  servo2.attach(servoMain);
  Serial.begin(115200);
  oPen();
  delay(4000);
  Serial.println(" READY ");
}

void loop()
{
  digitalWrite(trigPinHatch, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPinHatch, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinHatch, LOW);
  duration = pulseIn(echoPinHatch, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);
  
  int count = 0;
  
  while(in == false){
  digitalWrite(trigPinMain, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPinMain, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinMain, LOW);
    pulseIn(echoPinMain, HIGH);
  durationL = pulseIn(echoPinMain, HIGH);
  distanceL = durationL * 0.034 / 2;
    delay(1000);
    Serial.println("..."); 
    delay(10);
    
    if(distanceL >=10 && count != 2){
      in = true;
      done = true;
    }
    else if(count == 2){
      Serial.println();
      count = 0;
    }
    else{
      in = true;
      done = true;
    }
    count++;
    delayMicroseconds(10);
  }
  
  
  if(distance <= 30){
    Serial.println(" PLASTIC ");
    servo2.write(0);
    delay(1000); 
    if(done){
      oPen();
    }  
  }
  else if(distance <= 60  && distance != 30){
   Serial.println(" METAL ");
   servo2.write(90);
    delay(1000);

    if(done){
      oPen();
    }
  }
    else{
      Serial.println(" OTHERS ");
      servo2.write(180);
      delay(1000);
      
      if(done){
        oPen();
      }
    }
  delay(10);
}

void oPen(){
  servo1.write(0);
  delay(1000);
  servo1.write(180);
  done = false;
  in = false;
  Serial.println("Done");
}